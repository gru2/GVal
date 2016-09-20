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
	GVal(const GVal &x);
	~GVal();

	GVal &operator = (const GVal &x) { return *this; }
	bool operator < (const GVal &x) const { return false; }

	int getType() const { return type; }
	void setType(int x) { type = x; }

	GVal operator[] (size_t x) const { return *this; }

	void copyContentFrom(const GVal &x) {}
	void reset();
	size_t size();
	void resize(size_t x);
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

GVal::GVal(const GVal &x)
{
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
    }
}

void GVal::reset()
{
    genericValue.reset();
    type = GVT_NULL;
}

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "GVal test.\n";
}
