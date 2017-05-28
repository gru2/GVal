#include <GValSerializer.h>
#include <BinaryStream.h>

GValSerialzier::GValSerialzier()
{
	binaryStream = 0;
}

void GValSerialzier::write(const GVal &x)
{
	BinaryStream &bs = *binaryStream;
	int type = x.getType();
	bs.writeInt(type);
	switch (type) {
	case GVal::GVT_NULL:
		break;
	case GVal::GVT_BOOL:
		bs.writeInt(x.asBool());
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
	default:
		progressReporter.error("GValSerialzier::write bad GVal type "
		+ toString(type));
	}
}

GVal GValSerialzier::read()
{

}

GValSerialzier::writeMultiArray(GValMultiArray *x)
{
	BinaryStream &bs = *binaryStream;
	SmallVector<size_t, 4> &shape = x->getShape();
	int nDims = (int)shape.size();
	bs.writeInt((int)nDims);
	for (int i = 0; i < nDims; i++)
		bs.writeLong((long long)shape[i]);
}

GValSerialzier::writeMap(GValMap *x)
{

}
