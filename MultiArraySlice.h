#ifndef __MULTI_ARRAY_SLICE_H
#define __MULTI_ARRAY_SLICE_H

#include <SmallVector.h>
#include <cstddef>

class MultiArraySlice
{
public:
	SmallVector<size_t, 4> shape;
	SmallVector<size_t, 4> stride;
	size_t offset;

	MultiArraySlice();
	~MultiArraySlice();

	size_t calculateOffset(const SmallVector<size_t, 4> &inices);
	MultiArraySlice slice(unsigned dim, size_t index);
	void setWholeArray(const SmallVector<size_t, 4> &shape_);
};

#endif

