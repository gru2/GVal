#include <GVal.h>
#include <string.h>
#include <iostream>
#include <toString.h>

GVal &GVal::operator = (const GVal &x)
{
	copyContentFrom(x);
	return *this;
}
bool GVal::operator < (const GVal &x) const
{
	if (type != x.type)
		return type < x.type;
	switch (type)
	{
		case GVT_NULL:
			return false;
		case GVT_BOOL:
			return boolValue < x.boolValue;
		case GVT_INT:
			return intValue < x.intValue;
		case GVT_LONG:
			return longValue < x.longValue;
		case GVT_FLOAT:
			return floatValue < x.floatValue;
		case GVT_DOUBLE:
			return doubleValue < x.doubleValue;
		case GVT_STRING:
			return stringValue < x.stringValue;
		case GVT_MULTI_ARRAY:
		case GVT_MAP:
			return genericValue < x.genericValue; // TODO
			break;
	}
	return false;
}

GVal GVal::get(size_t i0) const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	return static_cast<GValMultiArray *>(genericValue.get())->get(&i0, 1);
}

GVal GVal::get(size_t i0, size_t i1) const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	size_t i[2];
	i[0] = i0;
	i[1] = i1;
	return static_cast<GValMultiArray *>(genericValue.get())->get(i, 2);
}

GVal GVal::get(size_t i0, size_t i1, size_t i2) const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	size_t i[3];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	return static_cast<GValMultiArray *>(genericValue.get())->get(i, 3);
}

GVal GVal::get(size_t i0, size_t i1, size_t i2, size_t i3) const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	size_t i[4];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	i[3] = i3;
	return static_cast<GValMultiArray *>(genericValue.get())->get(i, 4);
}

void GVal::set(size_t i0, const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return;
	}
	static_cast<GValMultiArray *>(genericValue.get())->set(&i0, 1, x);
}

void GVal::set(size_t i0, size_t i1, const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return;
	}
	size_t i[2];
	i[0] = i0;
	i[1] = i1;
	static_cast<GValMultiArray *>(genericValue.get())->set(i, 2, x);
}

void GVal::set(size_t i0, size_t i1, size_t i2, const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return;
	}
	size_t i[3];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	static_cast<GValMultiArray *>(genericValue.get())->set(i, 3, x);
}

void GVal::set(size_t i0, size_t i1, size_t i2, size_t i3, const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return;
	}
	size_t i[4];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	i[3] = i3;
	static_cast<GValMultiArray *>(genericValue.get())->set(i, 4, x);
}

GVal GVal::get(const SmallVector<size_t, 4> &i) const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	size_t s = i.size();
	size_t *p = i.begin();
	return static_cast<GValMultiArray *>(genericValue.get())->get(p, (int)s);
}

//GVal GVal::get(size_t *i, int dim) const
//{
//	if (type != GVT_MULTI_ARRAY)
//	{
//		error("multi array type expected.");
//		return GVal();
//	}
//	return static_cast<GValMultiArray *>(genericValue.get())->get(i, dim);
//}

GVal GVal::get(const std::string &key) const
{
	if (type != GVT_MAP)
	{
		error("multi array type expected.");
		return GVal();
	}
	GVal key_;
	key_.setString(key);
	return static_cast<GValMap *>(genericValue.get())->get(key_);
}

GVal GVal::get(const GVal &key) const
{
	if (type != GVT_MAP)
	{
		error("multi array type expected.");
		return GVal();
	}
	return static_cast<GValMap *>(genericValue.get())->get(key);
}

void GVal::set(const SmallVector<size_t, 4> &i, const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return;
	}
	size_t s = i.size();
	size_t *p = i.begin();
	static_cast<GValMultiArray *>(genericValue.get())->set(p, (int)s, x);
}

//void GVal::set(size_t *i, int dim, const GVal &x)
//{
//	if (type != GVT_MULTI_ARRAY)
//	{
//		error("multi array type expected.");
//		return;
//	}
//	static_cast<GValMultiArray *>(genericValue.get())->set(i, dim, x);
//}

void GVal::set(const std::string &key, const GVal &x)
{
	if (type != GVT_MAP)
	{
		error("multi array type expected.");
		return;
	}
	GVal key_;
	key_.setString(key);
	static_cast<GValMap *>(genericValue.get())->set(key_, x);
}

void GVal::set(const GVal &key, const GVal &x)
{
	if (type != GVT_MAP)
	{
		error("multi array type expected.");
		return;
	}
	static_cast<GValMap *>(genericValue.get())->set(key, x);
}

void GVal::copyContentFrom(const GVal &x)
{
	reset();
	type = x.type;
	switch(type)
	{
		case GVT_NULL:
			break;
		case GVT_BOOL:
			boolValue = x.boolValue;
			break;
		case GVT_INT:
			intValue = x.intValue;
			break;
		case GVT_LONG:
			longValue = x.longValue;
			break;
		case GVT_FLOAT:
			floatValue = x.floatValue;
			break;
		case GVT_DOUBLE:
			doubleValue = x.doubleValue;
			break;
		case GVT_STRING:
			stringValue = x.stringValue;
			break;
		case GVT_MULTI_ARRAY:
		case GVT_MAP:
			genericValue = x.genericValue;
			break;
	}
}

void GVal::reset()
{
	genericValue.reset();
	stringValue.clear();
	type = GVT_NULL;
}

size_t GVal::size() const
{
	switch(type)
	{
		case GVT_MULTI_ARRAY:
			return static_cast<GValMultiArray *>(genericValue.get())->size();
		case GVT_MAP:
			return static_cast<GValMap *>(genericValue.get())->size();
			break;
		default:
			error("type does not support size");
			return 0;
	}
}

const SmallVector<size_t, 4> &GVal::shape() const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("type does not support shape");
		//return SmallVector<size_t, 4>; // TODO
	}

	GValMultiArray *ma = static_cast<GValMultiArray *>(genericValue.get());
	return ma->getShape();
}

void GVal::resize(size_t x)
{
	resize(&x, 1);
}

void GVal::resize(size_t i0, size_t i1)
{
	size_t i[2];
	i[0] = i0;
	i[1] = i1;
	resize(i, 2);
}

void GVal::resize(size_t i0, size_t i1, size_t i2)
{
	size_t i[3];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	resize(i, 3);
}

void GVal::resize(size_t i0, size_t i1, size_t i2, size_t i3)
{
	size_t i[4];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	i[3] = i3;
	resize(i, 4);
}

void GVal::resize(const SmallVector<size_t, 4>& x)
{
	size_t s = x.size();
	size_t *p = x.begin();
	resize(p, (int)s);
}

void GVal::resize(size_t * i, int dim)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("type does not support resize");
		return;
	}

	GValMultiArray *ma = static_cast<GValMultiArray *>(genericValue.get());
	int entryType = ma->getEntryType();
	ma->resizeAndSetEntryType(i, dim, entryType);
}

void GVal::reshape(size_t i0)
{
	resize(i0);
}

void GVal::reshape(size_t i0, size_t i1)
{
	resize(i0, i1);
}

void GVal::reshape(size_t i0, size_t i1, size_t i2)
{
	resize(i0, i1, i2);
}

void GVal::reshape(size_t i0, size_t i1, size_t i2, size_t i3)
{
	resize(i0, i1, i2, i3);
}

void GVal::reshape(const SmallVector<size_t, 4>& x)
{
	resize(x);
}

void GVal::reshape(size_t * i, int dim)
{
	resize(i, dim);
}

GVal GVal::front() const
{
	return GVal(); // TODO
}

GVal GVal::back() const
{
	return GVal(); // TODO
}

void GVal::pushBack(const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("type " + toString(type) + " does not support pushBack");
		return;
	}
	static_cast<GValMultiArray *>(genericValue.get())->pushBack(x);
}

GVal GVal::popBack()
{
	return GVal(); // TODO
}

GVal GVal::keys() const
{
	return GVal(); // TODO
}

bool GVal::check(const std::string &key) const
{
	return check(GVal(key));
}

bool GVal::check(const GVal &key) const
{
	return false; // TODO
}

void GVal::setMultiArray(size_t i, int entryType)
{
	setMultiArray(&i, 1, entryType);
}
void GVal::setMultiArray(size_t i0, size_t i1, int entryType)
{
	size_t i[2];
	i[0] = i0;
	i[1] = i1;
	setMultiArray(i, 2, entryType);
}
void GVal::setMultiArray(size_t i0, size_t i1, size_t i2, int entryType)
{
	size_t i[3];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	setMultiArray(i, 3, entryType);
}
void GVal::setMultiArray(size_t i0, size_t i1, size_t i2, size_t i3, int entryType)
{
	size_t i[4];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	i[3] = i3;
	setMultiArray(i, 4, entryType);
}
void GVal::setMultiArray(const SmallVector<size_t, 4> &x, int entryType)
{
	size_t s = x.size();
	size_t *p = x.begin();
	setMultiArray(p, s, entryType);
}
void GVal::setMultiArray(size_t *i, size_t dim, int entryType)
{
	reset();
	type = GVT_MULTI_ARRAY;
	GValMultiArray *array = new GValMultiArray;
	genericValue = std::shared_ptr<GValMultiArray>(array);
	array->resizeAndSetEntryType(i, (int)dim, entryType);
}

void GVal::setMap()
{
	reset();
	type = GVT_MAP;
	GValMap *map = new GValMap;
	genericValue = std::shared_ptr<GValMap>(map);
}

void GVal::error(const std::string & msg) const
{
	progressReporter.error(msg);
}

std::string GVal::typeToString(int type_)
{
	switch(type_)
	{
		case GVT_NULL:
			return "Null";
		case GVT_BOOL:
			return "Bool";
		case GVT_INT:
			return "Int";
		case GVT_LONG:
			return "Long";
		case GVT_FLOAT:
			return "Float";
		case GVT_DOUBLE:
			return "Double";
		case GVT_STRING:
			return "String";
		case GVT_MULTI_ARRAY:
			return "MultiArray";
		case GVT_MAP:
			return "Map";
		case GVT_GENERIC:
			return "Generic";
		default:
			//return "Unknown(" + std::to_string("
			return "Unknown()";
	}
}

GValMultiArray::GValMultiArray()
{
	entryType = GVal::GVT_GENERIC;
	data = 0;
	capacity = 0;
}

GValMultiArray::~GValMultiArray()
{
	reset();
}

void GValMultiArray::reset()
{
	if (entryType == GVal::GVT_GENERIC)
	{
		size_t n = size();
		destroyObjects(static_cast<GVal *>(data), n);
	}
	if (data)
	{
		delete[] static_cast<char *>(data);
		data = nullptr;
	}
}

size_t GValMultiArray::size() const
{
	int nDims = shape.size();
	if (nDims == 0)
		return 0;
	size_t s = 1;
	for (int i = 0; i < nDims; i++)
		s *= shape[i];
	return s;
}

GVal GValMultiArray::get(size_t *i, int dim) const
{
	size_t offset = calculateOffset(i, dim);
	char *p1 = (char *)data + offset;
	void *p = static_cast<void *>(p1);
	GVal r;
	switch (entryType)
	{
	case GVal::GVT_BOOL:
		r.setBool(*static_cast<bool *>(p));
		break;
	case GVal::GVT_INT:
		r.setInt(*static_cast<int *>(p));
		break;
	case GVal::GVT_LONG:
		r.setLong(*static_cast<long long *>(p));
		break;
	case GVal::GVT_FLOAT:
		r.setFloat(*static_cast<float *>(p));
		break;
	case GVal::GVT_DOUBLE:
		r.setDouble(*static_cast<double *>(p));
		break;
	default:
		return *static_cast<GVal *>(p);
	}
	return r;
}

void GValMultiArray::set(size_t *i, int dim, const GVal &x)
{
	//std::cout << "GValMultiArray::set(*i = " << *i << ", dim = " << dim << ",..)\n";
	size_t offset = calculateOffset(i, dim);
	char *p1 = (char *)data + offset;
	void *p = static_cast<void *>(p1);
	//std::cout << "entryType = " << entryType << "\n";
	switch (entryType)
	{
	case GVal::GVT_BOOL:
		*static_cast<bool *>(p) = x.asBool();
		break;
	case GVal::GVT_INT:
		*static_cast<int *>(p) = x.asInt();
		break;
	case GVal::GVT_LONG:
		*static_cast<long long *>(p) = x.asLong();
		break;
	case GVal::GVT_FLOAT:
		*static_cast<float *>(p) = x.asFloat();
		break;
	case GVal::GVT_DOUBLE:
		*static_cast<double *>(p) = x.asDouble();
		break;
	default:
		*static_cast<GVal *>(p) = x;
		break;
	}
}

GVal GValMultiArray::front() const
{
	size_t index = 0;
	GVal r = get(&index, 1);
	return r;
}

GVal GValMultiArray::back() const
{
	size_t index = size() - 1;
	GVal r = get(&index, 1);
	return r;
}

void GValMultiArray::pushBack(const GVal &x)
{
	size_t index = size();
	size_t newSize = index + 1;
	resizeAndSetEntryType(&newSize, 1, entryType);
	set(&index, 1, x);
}

GVal GValMultiArray::popBack()
{
	size_t index = size() - 1;
	GVal r = get(&index, 1);
	resizeAndSetEntryType(&index, 1, entryType);
	return r;
}

void GValMultiArray::resizeAndSetEntryType(size_t *i, int dim, int newEntryType)
{
	// Calculate requred storage size for the new array.
	size_t newEntrysCount = 1;
	for(int j = 0; j < dim; j++)
		newEntrysCount *= i[j];
	size_t newEntrySize = getEntrySize(newEntryType);
	size_t requiredCapacity = newEntrysCount * newEntrySize;

	size_t oldEntrysCount = size();

	// Check if a new storage is required.
	if (capacity < requiredCapacity)
	{
		// Allocate the new storage and copy data if required.
		size_t newCapacity = capacity << 1;
		if (requiredCapacity > newCapacity)
			newCapacity = requiredCapacity;
		void *oldData = data;
		data = new char[newCapacity];

		if (newEntryType != GVal::GVT_GENERIC && entryType != GVal::GVT_GENERIC)
		{
			if (newEntryType == entryType)
				memcpy(data, oldData, oldEntrysCount * newEntrySize);
		}

		if (newEntryType == GVal::GVT_GENERIC && entryType == GVal::GVT_GENERIC)
			copyObjects(static_cast<GVal *>(data), static_cast<GVal *>(oldData), oldEntrysCount);

		if (newEntryType != GVal::GVT_GENERIC && entryType == GVal::GVT_GENERIC)
		{
			destroyObjects(static_cast<GVal *>(oldData), oldEntrysCount);
			entryType = newEntryType;
		}

		capacity = newCapacity;
	}

	// Construct or destruct objects if needed.
	size_t oldObjectsCount = 0;
	size_t newObjectsCount = 0;
	if (entryType == GVal::GVT_GENERIC)
		oldObjectsCount = oldEntrysCount;
	if (newEntryType == GVal::GVT_GENERIC)
		newObjectsCount = newEntrysCount;

	if (newObjectsCount > oldObjectsCount)
		createObjects((GVal *)data + oldObjectsCount, newObjectsCount - oldObjectsCount);
	if (newObjectsCount < oldObjectsCount)
		destroyObjects((GVal *)data + newObjectsCount, oldObjectsCount - newObjectsCount);

	// Set shape.
	shape.resize(dim);
	for(int j = 0; j < dim; j++)
		shape[j] = i[j];

	// Set the new entry type.
	entryType = newEntryType;
}

size_t GValMultiArray::getEntrySize(int type) const
{
	switch (type) {
	case GVal::GVT_BOOL:
		return sizeof(bool);
	case GVal::GVT_INT:
		return sizeof(int);
	case GVal::GVT_LONG:
		return sizeof(long long);
	case GVal::GVT_FLOAT:
		return sizeof(float);
	case GVal::GVT_DOUBLE:
		return sizeof(double);
	default:
		return sizeof(GVal);
	}
}

size_t GValMultiArray::calculateOffset(size_t *i, int dim) const
{
	size_t offsetIndex = 0;

	size_t s = 1;
	for (int j = dim - 1; j >= 0; j--)
	{
		offsetIndex += s * i[j];
		s *= shape[j];
	}

	size_t entrySize = getEntrySize(entryType);
	size_t offset = offsetIndex * entrySize;
	return offset;
}

void GValMultiArray::createObjects(GVal *objs, size_t count)
{
	GVal *p = objs;
	for (size_t i = 0; i < count; i++)
	{
		new (p) GVal;
		p++;
	}
}

void GValMultiArray::destroyObjects(GVal *objs, size_t count)
{
	GVal *p = objs;
	for (size_t i = 0; i < count; i++)
	{
		p->~GVal();
		p++;
	}
}

void GValMultiArray::copyObjects(GVal *dst, GVal *src, size_t count)
{
	GVal *d = dst;
	GVal *s = src;
	for (size_t i = 0; i < count; i++)
	{
		new (d) GVal (*s);
		d++;
		s++;
	}
}

GVal GValMap::get(const GVal &key)
{
	//std::cout << "GValMap::get(type=" << key.getType() << ")... \n";
	std::map<GVal, GVal>::iterator it = data.find(key);
	if (it == data.end())
		key.error("unable to find key.");
	return it->second;
}

void GValMap::set(const GVal &key, const GVal &value)
{
	data[key] = value;
}
