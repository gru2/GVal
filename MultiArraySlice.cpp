#include <MultiArraySlice.h>

MultiArraySlice::MultiArraySlice()
{
	offset = 0;
}

MultiArraySlice::~MultiArraySlice() { }

size_t MultiArraySlice::calculateOffset(const SmallVector<size_t, 4> &indices)
{
	size_t o = offset;
	int n = (int)shape.size();
	for (int i = 0; i < n; i++)
		o += stride[i] * indices[i];
	return o;
}

MultiArraySlice MultiArraySlice::slice(unsigned dim, size_t index)
{
	MultiArraySlice newSlice;
	int n = (int)shape.size();
	for (int i = 0; i < n; i++)
	{
		if (i != dim)
		{
			newSlice.shape.push_back(shape[i]);
			newSlice.stride.push_back(stride[i]);
		}
	}
	offset = stride[dim] * index;
}

void MultiArraySlice::setWholeArray(const SmallVector<size_t, 4> &shape_)
{
	shape = shape_;
	int n = (int)shape.size();
	shape.resize(n);
	size_t m = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		shape[i] = m;
		m *= shape[i];
	}
}
