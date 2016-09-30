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
	enum GValType { GVT_NULL, GVT_BOOL, GVT_INT, GVT_LONG_LONG, GVT_FLOAT, GVT_DOUBLE,
		GVT_MULTI_ARRAY, GVT_MAP, GVT_GENERIC };

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

	GVal operator[] (size_t x) const { return *this; }

	void copyContentFrom(const GVal &x);
	void reset();
	size_t size();
	void resize(size_t x);

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
	void setFloat(float x) {
		reset();
		type = GVT_FLOAT;
		intFloat = x;
	}
	void setDouble(double x) {
		reset();
		type = GVT_DOUBLE;
		intFloat = x;
	}
	void setString(const std::string &x) {
		reset();
		type = GVT_STRING;
		intString = x;
	}

protected:
	int type;
	union
	{
		bool boolValue;
		int intValue;
		long long longLongValue;
		float floatValue;
		double doubleValue;
	};
	std::shared_ptr<void> genericValue;
	SmallString<32> stringValue;
};

class GValMultiArray
{
protected:
	int entryType;
	SmallVector<unsigned, 8> dimensions;
	void *data;
};

class GValMap
{
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
		case GVT_LONG_LONG:
			return longLongValue < x.longLongValue;
		case GVT_FLOAT:
			return floatValue < x.floatValue;
		case GVT_DOUBLE:
			return doubleValue < x.doubleValue;
		case GVT_MULTI_ARRAY:
			
		case GVT_MAP:
			return genericValue < x.genericValue; // TODO
			break;
	}
	return false;
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
		case GVT_LONG_LONG:
			longLongValue = x.longLongValue;
			break;
		case GVT_FLOAT:
			floatValue = x.floatValue;
			break;
		case GVT_DOUBLE:
			doubleValue = x.doubleValue;
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
	type = GVT_NULL;
}

size_t GVal::size()
{
	switch(type)
	{
		case GVT_MULTI_ARRAY:
			return static_cast<GValMultiArray *>(r.get())->size();
		case GVT_MAP:
			return static_cast<GValMap *>(r.get())->size();
			break;
		default:
			error("type does not support size");
	}
}

void GVal::resize(size_t x)
{
}

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "GVal test.\n";
	
	GVal val;
}
