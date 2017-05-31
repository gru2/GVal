#include <GValSerializer.h>
#include <BinaryStream.h>

GValSerializer::GValSerializer()
{
	binaryStream = 0;
}

void GValSerializer::write(const GVal &x)
{
	BinaryStream &bs = *binaryStream;
	int type = x.getType();
	bs.writeInt(type);
	switch (type) {
	case GVal::GVT_NULL:
		break;
	case GVal::GVT_BOOL:
		bs.writeByte(x.asBool());
		break;
	case GVal::GVT_INT:
		bs.writeInt(x.asInt());
		break;
	case GVal::GVT_LONG:
		bs.writeLong(x.asLong());
		break;
	case GVal::GVT_FLOAT:
		bs.writeFloat(x.asFloat());
		break;
	case GVal::GVT_DOUBLE:
		bs.writeDouble(x.asDouble());
		break;
	case GVal::GVT_STRING:
		bs.writeString(x.asString());
		break;
	case GVal::GVT_MULTI_ARRAY:
		writeMultiArray(x);
		break;
	case GVal::GVT_MAP:
		writeMap(x);
		break;
	default:
		progressReporter.error("GValSerialzier::write:bad GVal type "
		+ toString(type));
		break;
	}
}

GVal GValSerializer::read()
{
	BinaryStream &bs = *binaryStream;
	int type = bs.readInt();
	switch (type)
	{
	case GVal::GVT_BOOL:
	{
		char c = bs.readByte();
		bool x = c ? true : false;
		return GVal(x);
	}
	case GVal::GVT_INT:
	{
		int x = bs.readInt();
		return GVal(x);
	}
	case GVal::GVT_LONG:
	{
		long long x = bs.readLong();
		return GVal(x);
	}
	case GVal::GVT_FLOAT:
	{
		float x = bs.readFloat();
		return GVal(x);
	}
	case GVal::GVT_DOUBLE:
	{
		double x = bs.readDouble();
		return GVal(x);
	}
	case GVal::GVT_STRING:
	{
		std::string x = bs.readString();
		return GVal(x);
	}
	case GVal::GVT_MULTI_ARRAY:
		return readMultiArray();
	case GVal::GVT_MAP:
		return readMap();
	default:
		progressReporter.error("GValSerialzier::read:bad GVal type "
		+ toString(type));
	}
	return GVal();
}

GVal GValSerializer::readMultiArray()
{
	BinaryStream &bs = *binaryStream;
	int entryType = bs.readInt();
	int nDims = bs.readInt();
	SmallVector<size_t, 4> shape;
	shape.resize(nDims);
	for (int i = 0; i < nDims; i++)
		shape[i] = bs.readLong();
	GVal r;
	r.setMultiArray(shape, entryType);
	size_t n = r.size();
	void *data = r.getData();
	switch (entryType)
	{
	case GVal::GVT_BOOL:
	{
		bool *p = static_cast<bool *>(data);
		for (size_t i = 0; i < n; i++)
		{
			char c = bs.readByte();
			bool x = c ? true : false;
			*p++ = x;
		}	
		break;
	}
	case GVal::GVT_INT:
	{
		int *p = static_cast<int *>(data);
		for (size_t i = 0; i < n; i++)
			*p++ = bs.readInt();
		break;
	}
	case GVal::GVT_LONG:
	{
		long long *p = static_cast<long long *>(data);
		for (size_t i = 0; i < n; i++)
			*p++ = bs.readLong();
		break;
	}
	case GVal::GVT_FLOAT:
	{
		float *p = static_cast<float *>(data);
		for (size_t i = 0; i < n; i++)
			*p++ = bs.readFloat();
		break;
	}
	case GVal::GVT_DOUBLE:
	{
		double *p = static_cast<double *>(data);
		for (size_t i = 0; i < n; i++)
			*p++ = bs.readDouble();
		break;
	}
	case GVal::GVT_GENERIC:
	{
		GVal *p = static_cast<GVal *>(data);
		for (size_t i = 0; i < n; i++)
			*p++ = read();
		break;
	}
	default:
		progressReporter.error("GValSerialzier::readMultiArray:bad entry type "
		+ toString(entryType));
		break;
	}
	return r;
}

GVal GValSerializer::readMap()
{
	GVal r;
	r.setMap();
	size_t n = binaryStream->readLong();
	for (int i = 0; i < n; i++)
	{
		GVal key = read();
		GVal value = read();
		r.set(key, value);
	}
	return r;
}

void GValSerializer::writeMultiArray(const GVal &x)
{
	ProgressReporter &pr = progressReporter;
	if (x.getType() != GVal::GVT_MULTI_ARRAY)
		pr.error("GValSerialzier::writeMultiArray:not multi array");
	const std::shared_ptr<void> genericValue = x.getGenericValue();
	GValMultiArray *ma = static_cast<GValMultiArray *>(genericValue.get());
	BinaryStream &bs = *binaryStream;
	int entryType = ma->getEntryType();
	bs.writeInt(entryType);
	const SmallVector<size_t, 4> &shape = ma->getShape();
	int nDims = (int)shape.size();
	bs.writeInt((int)nDims);
	for (int i = 0; i < nDims; i++)
		bs.writeLong((long long)shape[i]);
	void *data = ma->getData();
	size_t n = ma->size();
	switch (entryType)
	{
	case GVal::GVT_BOOL:
	{
		bool *p = static_cast<bool *>(data);
		for (size_t i = 0; i < n; i++)
			bs.writeByte(*p++);
		break;
	}
	case GVal::GVT_INT:
	{
		int *p = static_cast<int *>(data);
		for (size_t i = 0; i < n; i++)
			bs.writeInt(*p++);
		break;
	}
	case GVal::GVT_LONG:
	{
		long long *p = static_cast<long long *>(data);
		for (size_t i = 0; i < n; i++)
			bs.writeLong(*p++);
		break;
	}
	case GVal::GVT_FLOAT:
	{
		float *p = static_cast<float *>(data);
		for (size_t i = 0; i < n; i++)
			bs.writeFloat(*p++);
		break;
	}
	case GVal::GVT_DOUBLE:
	{
		double *p = static_cast<double *>(data);
		for (size_t i = 0; i < n; i++)
			bs.writeDouble(*p++);
		break;
	}
	case GVal::GVT_GENERIC:
	{
		GVal *p = static_cast<GVal *>(data);
		for (size_t i = 0; i < n; i++)
			write(*p++);
		break;
	}
	default:
		pr.error("GValSerialzier::writeMultiArray:unknown entry type");
		break;
	}
}

void GValSerializer::writeMap(const GVal &x)
{
	ProgressReporter &pr = progressReporter;
	if (x.getType() != GVal::GVT_MAP)
		pr.error("GValSerialzier::writeMultiArray:not map");
	const std::shared_ptr<void> genericValue = x.getGenericValue();
	GValMap *map = static_cast<GValMap *>(genericValue.get());
	std::string r = "{";
	size_t n = map->size();
	binaryStream->writeLong(n);
	GVal keys = map->keys();
	for (size_t i = 0; i < n; i++)
	{
		GVal key = keys[i];
		GVal value = x.get(key);
		write(key);
		write(value);
	}
}
