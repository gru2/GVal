#include <MultiArraySlice.h>

MultiArraySlice::MultiArraySlice()
{
	offset = 0;
}

MultiArraySlice::~MultiArraySlice() { }

size_t MultiArraySlice::calculateOffset(const SmallVector<size_t, 4> &indices) const
{
	size_t o = offset;
	int n = (int)shape.size();
	for (int i = 0; i < n; i++)
		o += stride[i] * indices[i];
	return o;
}

MultiArraySlice MultiArraySlice::slice(unsigned dim, size_t index) const
{
	MultiArraySlice newSlice;
	int n = (int)shape.size();
	for (int i = 0; i < n; i++)
	{
		if (i != (int)dim)
		{
			newSlice.shape.push_back(shape[i]);
			newSlice.stride.push_back(stride[i]);
		}
	}
	newSlice.offset = offset + stride[dim] * index;
	return newSlice;
}

void MultiArraySlice::setWholeArray(const SmallVector<size_t, 4> &shape_)
{
	shape = shape_;
	int n = (int)shape.size();
	stride.resize(n);
	size_t m = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		stride[i] = m;
		m *= shape[i];
	}
	offset = 0;
}
