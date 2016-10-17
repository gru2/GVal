#ifndef __PROGRESS_REPORTER_H
#define __PROGRESS_REPORTER_H

#include <string>

class ProgressReporter
{
public:
	void error(const std::string &msg);
};

#endif

//#include <ProgressReporter.h>
#include <stdio.h>
#include <stdlib.h>

void ProgressReporter::error(const std::string &msg)
{
	printf("error:%s\n", msg.c_str());
	exit(1);
}

#ifndef __SMALL_VECTOR_H
#define __SMALL_VECTOR_H

template<typename T, unsigned N>
class SmallVector
{
public:
	SmallVector<T, N>()
	{
		size_ = 0;
		capacity = N;
		data = &localStorage[0];
	}
	SmallVector<T, N>(unsigned n)
	{
		size_ = 0;
		capacity = N;
		data = &localStorage[0];
		if (n <= N)
		{
			size_ = n;
			return;
		}
		grow(n);
		size_ = n;
	}
	SmallVector<T, N>(const SmallVector<T, N> &x)
	{
		capacity = N;
		data = &localStorage[0];
		if (x.size_ > N)
		{
			size_ = 0;
			grow(x.size_);
		}
		size_ = x.size_;
		for (unsigned i = 0; i < x.size_; i++)
			data[i] = x.data[i];
	}
	~SmallVector<T, N>()
	{
		if (capacity > N)
			delete [] data;
	}

	const SmallVector<T, N> &operator=(const SmallVector<T, N> &x)
	{
		if (capacity < x.size_)
			grow(x.size_);
		size_ = x.size_;
		for (unsigned i = 0; i < x.size_; i++)
			data[i] = x.data[i];
	}

	unsigned size() const { return size_; }
	T *begin() const
	{
		return data;
	}
	T *end() const
	{
		return data + size_;
	}
	void resize(unsigned n)
	{
		if (capacity < n)
			grow(n);
		size_ = n;
	}
	void clear()
	{
		resize(0);
	}
	void push_back(const T &x)
	{
		resize(size_ + 1);
		data[size_ - 1] = x;
	}
	void pop_back()
	{
		resize(size_ - 1);
	}
	T &operator [](unsigned i)
	{
		return data[i];
	}

protected:
	void grow(int n);
	unsigned size_;
	unsigned capacity;
	T *data;
	T localStorage[N];
};

template<typename T, unsigned N>
void SmallVector<T, N>::grow(int n)
{
	if (n <= capacity)
		return;

	unsigned newCapacity = n;
	if ((capacity << 1) > newCapacity)
		newCapacity = capacity << 1;

	T *newData = new T[newCapacity];

	for (unsigned i=0; i < size_; i++)
		newData[i] = data[i];

	if (capacity > N)
		delete [] data;

	capacity = newCapacity;
	data = newData;
}

#endif



//#ifndef __GVAL_H
//#define __GVAL_H

#include <cstdint>
#include <memory>
#include <map>

class GVal
{
public:
	enum GValType { GVT_NULL, GVT_BOOL, GVT_INT, GVT_LONG, GVT_FLOAT, GVT_DOUBLE,
		GVT_STRING, GVT_MULTI_ARRAY, GVT_MAP, GVT_GENERIC };

	GVal() : type(GVT_NULL) { }
	GVal(const GVal &x) {
		copyContentFrom(x);
	}
	~GVal() {
		reset();
	}

	GVal &operator = (const GVal &x);
	bool operator < (const GVal &x) const;

	int getType() const { return type; }
	void setType(int x) { type = x; }

	GVal operator[] (size_t i) const { return get(i); }
	GVal operator[] (const std::string &key) const { get(key); }
	GVal operator() (size_t i0, size_t i1) const { return get(i0, i1); }
	GVal operator() (size_t i0, size_t i1, size_t i2) const { return get(i0, i1, i2); }
	GVal operator() (size_t i0, size_t i1, size_t i2, size_t i3) const { return get(i0, i1, i2, i3); }

	GVal get(size_t i0) const;
	GVal get(size_t i0, size_t i1) const;
	GVal get(size_t i0, size_t i1, size_t i2) const;
	GVal get(size_t i0, size_t i1, size_t i2, size_t i3) const;
	void set(size_t i0, const GVal &x);
	void set(size_t i0, size_t i1, const GVal &x);
	void set(size_t i0, size_t i1, size_t i2, const GVal &x);
	void set(size_t i0, size_t i1, size_t i2, size_t i3, const GVal &x);
	GVal get(const SmallVector<size_t, 4> &i) const;
	GVal get(size_t *i, int dim) const;
	GVal get(const std::string &key) const;
	GVal get(const GVal &key) const;
	GVal set(const SmallVector<size_t, 4> &i, GVal &x);
	GVal set(size_t *i, int dim, GVal &x);
	GVal set(const std::string &key, GVal &x);
	GVal set(GVal &key, GVal &x);

	void copyContentFrom(const GVal &x);
	void reset();
	size_t size() const;
	size_t size(int dim) const { return dimensions()[dim]; }
	const SmallVector<size_t, 4> &dimensions() const;
	size_t numberOfDimensions() const { return dimensions.size(); }
	void resize(size_t i0);
	void resize(size_t i0, size_t i1);
	void resize(size_t i0, size_t i1, size_t i2);
	void resize(size_t i0, size_t i1, size_t i2, size_t i3);
	void resize(const SmallVector<size_t, 4> &x);
	void resize(size_t *i, int dim);

	void reshape(size_t i0);
	void reshape(size_t i0, size_t i1);
	void reshape(size_t i0, size_t i1, size_t i2);
	void reshape(size_t i0, size_t i1, size_t i2, size_t i3);
	void reshape(const SmallVector<size_t, 4> &x);
	void reshape(size_t *i, int dim);

	GVal front() const;
	GVal back() const;

	void pushBack(const GVal &x);
	GVal popBack();

	GVal keys() const;
	bool check(const std::string &key) const;
	bool check(GVal &key) const;

	void setNull() {
		reset();
		type = GVT_NULL;
	}
	void setBool(bool x) {
		reset();
		type = GVT_BOOL;
		boolValue = x;
	}
	void setInt(int x) {
		reset();
		type = GVT_INT;
		intValue = x;
	}
	void setLong(long long x) {
		reset();
		type = GVT_LONG;
		longValue = x;
	}
	void setFloat(float x) {
		reset();
		type = GVT_FLOAT;
		floatValue = x;
	}
	void setDouble(double x) {
		reset();
		type = GVT_DOUBLE;
		doubleValue = x;
	}
	void setString(const std::string &x) {
		reset();
		type = GVT_STRING;
		stringValue = x;
	}
	void setMultiArray(size_t i, int entryType);
	void setMultiArray(size_t i0, size_t i1, int entryType);
	void setMultiArray(size_t i0, size_t i1, size_t i2, int entryType);
	void setMultiArray(size_t i0, size_t i1, size_t i2, size_t i3, int entryType);
	void setMultiArray(const SmallVector<size_t, 4> &x, int entryType);
	void setMultiArray(size_t *i, size_t dim, int entryType);
	void setMap();
	void setMap(int keyType_, int valueType_);

	bool isNull() const {
		return type == GVT_NULL;
	}
	bool asBool() const {
		if (type != GVT_BOOL)
			error("Bool type expected.");
		return boolValue;
	}
	int asInt() const {
		if (type != GVT_INT)
			error("Int type expected.");
		return intValue;
	}
	long long asLong() const {
		if (type != GVT_LONG)
			error("Long type expected.");
		return longValue;
	}
	int asFloat() const {
		if (type != GVT_FLOAT)
			error("Float type expected.");
		return floatValue;
	}
	int asDouble() const {
		if (type != GVT_DOUBLE)
			error("Double type expected.");
		return doubleValue;
	}
	std::string &asString() const {
		if (type != GVT_STRING)
			error("String type expected.");
		return stringValue;
	}

protected:
	int type;
	union
	{
		bool boolValue;
		int intValue;
		long long longValue;
		float floatValue;
		double doubleValue;
	};
	std::shared_ptr<void> genericValue;
	std::string stringValue;
	ProgressReporter progressReporter;

	void error(const std::string &msg);
};

class GValMultiArray
{
public:
	GValMultiArray();
	~GValMultiArray();

	void reset();

	size_t size();
	GVal get(size_t *i, int dim);
	void set(size_t *i, int dim, const GVal &x);

	GVal front() const;
	GVal back() const;

	void pushBack(const GVal &x);
	GVal popBack();

	int getEntryType() const { return entryType; }
	void allocateArray(size_t *i, int dim, int entryType_);
protected:
	int entryType;
	SmallVector<size_t, 4> dimensions;
	size_t capacity;
	void *data;

	size_t getEntrySize(int type);
	size_t calculateOffset(size_t *i, int dim);
	void createObjects(GVal *objs, size_t count);
	void destroyObjects(GVal *objs, size_t count);
	void copyObjects(GVal *objs, size_t count);
};

class GValMap
{
public:
	size_t size() { return data.size(); }
protected:
	int keyType;
	int valueType;
	std::map<GVal, GVal> data;
};

//#endif

// ---------------GVal.cpp
//#include <GVal.h>

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
		return GVal();
	}
	static_cast<GValMultiArray *>(genericValue.get())->set(&i0, 1, x);
}
void GVal::set(size_t i0, size_t i1, const GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	size_t i[2];
	i[0] = i0;
	i[1] = i1;
	static_cast<GValMultiArray *>(genericValue.get())->set(&i, 2, x);
}
void GVal::set(size_t i0, size_t i1, size_t i2, const GVal &x)
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
	static_cast<GValMultiArray *>(genericValue.get())->set(&i, 3, x);
}
void GVal::set(size_t i0, size_t i1, size_t i2, size_t i3, const GVal &x)
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
	static_cast<GValMultiArray *>(genericValue.get())->set(&i, 4, x);
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
	return static_cast<GValMultiArray *>(genericValue.get())->get(p, s);
}
GVal GVal::get(size_t *i, int dim) const
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	return static_cast<GValMultiArray *>(genericValue.get())->get(i, dim);
}
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
GVal GVal::set(const SmallVector<size_t, 4> &i, GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	size_t s = i.size();
	size_t *p = i.begin();
	static_cast<GValMultiArray *>(genericValue.get())->set(p, s, x);
}
GVal GVal::set(size_t *i, int dim, GVal &x)
{
	if (type != GVT_MULTI_ARRAY)
	{
		error("multi array type expected.");
		return GVal();
	}
	static_cast<GValMultiArray *>(genericValue.get())->set(i, dim, x);
}
GVal GVal::set(const std::string &key, GVal &x)
{
	if (type != GVT_MAP)
	{
		error("multi array type expected.");
		return GVal();
	}
	GVal key_;
	key_.setString(key);
	static_cast<GValMap *>(genericValue.get())->set(key_, x);
}
GVal GVal::set(GVal &key, GVal &x)
{
	if (type != GVT_MAP)
	{
		error("multi array type expected.");
		return GVal();
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

size_t GVal::size()
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
	}
}

void GVal::resize(size_t x)
{
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
	setMultiArray(&i, 2, entryType);
}
void GVal::setMultiArray(size_t i0, size_t i1, size_t i2, int entryType)
{
	size_t i[3];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	setMultiArray(&i, 3, entryType);
}
void GVal::setMultiArray(size_t i0, size_t i1, size_t i2, size_t i3, int entryType)
{
	size_t i[4];
	i[0] = i0;
	i[1] = i1;
	i[2] = i2;
	i[3] = i3;
	setMultiArray(&i, 4, entryType);
}
void GVal::setMultiArray(const SmallVector<size_t, 4> &x, int entryType)
{
	size_t s = x.size();
	size_t *p = x.begin();
	setMultiArray(&p, s, entryType);
}
void GVal::setMultiArray(size_t *i, size_t dim, int entryType)
{
	reset();
	type = GVT_MULTI_ARRAY;
	GValMultiArray *array = new GValMultiArray;
	genericValue = shared_ptr<GValMultiArray>(array);
	array->setType(entryType);
	array->allocateArray(i, dim, entryType);
}

GVal GValMultiArray::get(size_t *i, int dim)
{
	size_t offset = calculateOffset(i, dim);
	char *p = (char *)data + offset;
	GVal r;
	switch (entryType)
	{
	case GVT_BOOL:
		return *static_cast<bool>(p);
	case GVT_INT:
		return *static_cast<int>(p);
	case GVT_LONG:
		return *static_cast<long long>(p);
	case GVT_FLOAT:
		return *static_cast<float>(p);
	case GVT_DOUBLE:
		return *static_cast<double>(p);
	default:
		return *static_cast<GVAl>(p);
	}
	return r;
}

void GValMultiArray::set(size_t *i, int dim, const GVal &x)
{
	size_t offset = calculateOffset(i, dim);
	char *p = (char *)data + offset;
	switch (entryType)
	{
	case GVT_BOOL:
		*static_cast<bool>(p) = x.asBool();
	case GVT_INT:
		*static_cast<int>(p) = x.asInt();
	case GVT_LONG:
		*static_cast<long long>(p) = x.asLong();
	case GVT_FLOAT:
		*static_cast<float>(p) = x.asFloat();
	case GVT_DOUBLE:
		*static_cast<double>(p) = x.asDouble();
	default:
		*static_cast<GVal>(p) = x;
	}
}

void GValMultiArray::allocateArray(size_t *i, int dim, int entryType_)
{
	size_t entryCount = 1;
	for(int j = 0; j < dim; j++)
		entryCount *= i[j];
	size_t entrySize = getEntrySize(entryType_);
	int requiredCapacity = entryCount * entrySize;
	if (capacity < requiredCapacity)
	{
		size_t oldSize = size();
		void *oldData = data;
		data = new char[requiredCapacity];
		memcpy(data, oldData, oldSize * entrySize);
		capacity = requiredCapacity;
	}
	dimensions.resize(dim);
	for(int j = 0; j < dim; j++)
		dimensions[j] = i[j];
}

size_t GValMultiArray::getEntrySize(int type)
{
	switch (type) {
	case GVT_BOOL:
		return sizeof(bool);
	case GVT_INT:
		return sizeof(int);
	case GVT_LONG:
		return sizeof(long long);
	case GVT_FLOAT:
		return sizeof(float);
	case GVT_DOUBLE:
		return sizeof(double);
	default:
		return sizeof(GVal);
	}
}

size_t GValMultiArray::calculateOffset(size_t *i, int dim)
{
	size_t offsetIndex = 0;

	size_t s = 1;
	for (int j = dim - 1; j >= 0; j--)
	{
		offsetIndex += s * i[j];
		s *= dimensions[j];
	}

	size_t entrySize = getEntrySize(entryType);
	size_t offset = offsetIndex * entrySize;
	return offset;
}

void GValMultiArray::createObjects(GVal *objs, size_t count)
{
	GVal *p = objs;
	for (size i = 0; i < count; i++)
	{
		new GVal(p) ();
		p++;
	}
}

void GValMultiArray::destroyObjects(GVal *objs, size_t count)
{
	GVal *p = objs;
	for (size i = 0; i < count; i++)
	{
		p->~GVal();
		p++;
	}
}

void GValMultiArray::copyObjects(GVal *dst, GVal *src, size_t count)
{
	GVal *d = dst;
	GVal *s = src;
	for (size i = 0; i < count; i++)
	{
		new GVal(d) (*s);
		d++;
		s++;
	}
}

//GValTest.cpp

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "GVal test.\n";
	
	GVal val;
}
