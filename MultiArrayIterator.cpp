#include <MultiArrayIterator.h>

MultiArrayIterator::MultiArrayIterator()
{
	atEnd_ = false;
}

MultiArrayIterator::MultiArrayIterator(const SmallVector<size_t, 4> &shape_)
{
	shape = shape_;
	setBegin();
}

MultiArrayIterator::~MultiArrayIterator() { }

void MultiArrayIterator::setBegin()
{
	atEnd_ = false;
	unsigned n = shape.size();
	indices.resize(n);
	for (unsigned i = 0; i < n; i++)
		indices[i] = 0;
	size_t len = shapeLength(shape);
	if (len == 0)
		atEnd_ = true;
}

bool MultiArrayIterator::atEnd()
{
	return atEnd_;
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
	atEnd_ = true;
}

size_t MultiArrayIterator::shapeLength(const SmallVector<size_t, 4> &shape_)
{
	unsigned n = shape.size();
	if (n == 0)
		return 0;
	size_t len = 1;
	for(unsigned i = 0; i < n; i++)
		len *= shape_[i];
	return len;
}
