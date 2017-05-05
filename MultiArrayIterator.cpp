#include <MultiArrayIterator.h>

MultiArrayIterator::MultiArrayIterator() { }

MultiArrayIterator::MultiArrayIterator(const SmallVector<size_t, 4> &shape_)
{
	shape = shape_;
	setBegin();
}

MultiArrayIterator::~MultiArrayIterator() { }

void MultiArrayIterator::setBegin()
{
	unsigned n = shape.size();
	indices.resize(n);
	for (unsigned i = 0; i < n; i++)
		indices[i] = 0;
}

bool MultiArrayIterator::atEnd()
{
	int n = int(shape.size());
	for(int i = n - 1; i >= 0; i--)
	{
		if ((indices[i] + 1) < shape[i])
			return false;
	}
	return true;
}

void MultiArrayIterator::next()
{
	int n = int(shape.size());
	for(int i = n - 1; i >= 0; i--)
	{
		indices[i]++;
		if (indices[i] < shape[i])
			return;
		indices[i] = 0;
	}
}
