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

#ifndef __SMALL_STRING_H
#define __SMALL_STRING_H

template<unsigned N>
class SmallString
{
public:
	SmallString<N>()
	{
		size_ = 0;
		capacity = N - 1;
		data = &localStorage[0];
	}
	SmallString<N>(unsigned n)
	{
		size_ = 0;
		capacity = N - 1;
		data = &localStorage[0];
		if (n <= capacity)
		{
			size_ = n;
			return;
		}
		grow(n);
		size_ = n;
		data[size_] = 0;
	}
	SmallString<N>(const SmallString<N> &x)
	{
		capacity = N - 1;
		data = &localStorage[0];
		if (x.size_ > capacity)
		{
			size_ = 0;
			grow(x.size_);
		}
		size_ = x.size_;
		for (unsigned i = 0; i < x.size_ + 1; i++)
			data[i] = x.data[i];
	}
	SmallString<N>(const char *x)
	{
		unsigned len = 0;
		for (;;)
		{
			if (x[len] == 0)
				break;
			len++;
		}
		capacity = N - 1;
		data = &localStorage[0];
		if (len > capacity)
		{
			size_ = 0;
			grow(len);
		}
		size_ = len;
		for (unsigned i = 0; i < size_ + 1; i++)
			data[i] = x[i];
	}
	~SmallString<N>()
	{
		if (capacity >= N)
			delete[] data;
	}

	const SmallString<N> &operator=(const SmallString<N> &x)
	{
		if (capacity < x.size_)
			grow(x.size_);
		size_ = x.size_;
		for (unsigned i = 0; i < x.size_; i++)
			data[i] = x.data[i];
		return this;
	}
	const SmallString<N> &operator=(const char *x)
	{
		unsigned len = 0;
		for (;;)
		{
			if (x[len] == 0)
				break;
			len++;
		}
		if (capacity < len)
			grow(len);
		for (unsigned i = 0; i < size_ + 1; i++)
			data[i] = x[i];
		return this;
	}

	unsigned size() const { return size_; }
	char *begin() const
	{
		return data;
	}
	char *end() const
	{
		return data + size_;
	}
	void resize(unsigned n)
	{
		if (capacity < n)
			grow(n);
		size_ = n;
		data[n] = 0;
	}
	void clear()
	{
		resize(0);
	}
	void push_back(char x)
	{
		resize(size_ + 1);
		data[size_ - 1] = x;
		data[size_] = 0;
	}
	char &operator [](unsigned i)
	{
		return data[i];
	}
	void operator +=(const SmallString<N> &x)
	{
		unsigned n = size_;
		resize(n + x.size_);
		for (unsigned i = 0; i < x.size_ + 1; i++)
			data[n + i] = x.data[i];
	}
	void operator +=(const char *x)
	{
		unsigned len = 0;
		for (;;)
		{
			if (x[len] == 0)
				break;
			len++;
		}
		unsigned n = size_;
		resize(n + len);
		for (unsigned i = 0; i < len + 1; i++)
			data[n + i] = x[i];
	}
	char *str() { return data; }
	bool operator ==(const SmallString<N> &x) const
	{
		if (size_ != x.size_)
			return false;
		for (unsigned i = 0; i < size_; i++)
			if (data[i] != x.data[i])
				return false;
		return true;
	}
	bool operator ==(const char *x) const
	{
		unsigned len = 0;
		for (;;)
		{
			if (x[len] == 0)
				break;
			len++;
		}
		if (size_ != len)
			return false;
		for (unsigned i = 0; i < size_; i++)
			if (data[i] != x[i])
				return false;
		return true;
	}
	bool operator <(const SmallString<N> &x) const
	{
		unsigned n = size_;
		if (x.size_ < n)
			n = x.size_;
		for (unsigned i = 0; i < n; i++)
			if (data[i] != x.data[i])
				return data[i] < x.data[i];
		if (n < x.size_)
			return true;
		return false;
	}
	bool operator <(const char *x) const
	{
		unsigned len = 0;
		for (;;)
		{
			if (x[len] == 0)
				break;
			len++;
		}
		unsigned n = size_;
		if (len < n)
			n = len;
		for (unsigned i = 0; i < n; i++)
			if (data[i] != x[i])
				return data[i] < x[i];
		if (n < len)
			return true;
		return false;
	}

protected:
	void grow(unsigned n);
	unsigned size_;
	unsigned capacity;
	char *data;
	char localStorage[N];
};

template<unsigned N>
void SmallString<N>::grow(unsigned n)
{
	if (n < capacity)
		return;

	unsigned newCapacity = n;
	if ((capacity << 1) > newCapacity)
		newCapacity = capacity << 1;

	char *newData = new char[newCapacity + 1];

	for (unsigned i = 0; i < size_ + 1; i++)
		newData[i] = data[i];

	if (capacity >= N)
		delete[] data;

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
		case GVT_STRING:
			return stringValue < x.stringValue;
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
	stringValue.reset();
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
