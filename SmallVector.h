#ifndef GVAL_SMALL_VECTOR_H
#define GVAL_SMALL_VECTOR_H

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
			delete[] data;
	}

	const SmallVector<T, N> &operator=(const SmallVector<T, N> &x)
	{
		if (capacity < x.size_)
			grow(x.size_);
		size_ = x.size_;
		for (unsigned i = 0; i < x.size_; i++)
			data[i] = x.data[i];
		return *this;
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
	const T &operator [](unsigned i) const
	{
		return data[i];
	}

protected:
	void grow(unsigned n);
	unsigned size_;
	unsigned capacity;
	T *data;
	T localStorage[N];
};

template<typename T, unsigned N>
void SmallVector<T, N>::grow(unsigned n)
{
	if (n <= capacity)
		return;

	unsigned newCapacity = n;
	if ((capacity << 1) > newCapacity)
		newCapacity = capacity << 1;

	T *newData = new T[newCapacity];

	for (unsigned i = 0; i < size_; i++)
		newData[i] = data[i];

	if (capacity > N)
		delete[] data;

	capacity = newCapacity;
	data = newData;
}

#endif
