#ifndef __MULTI_ARRAY_ITERATOR_H
#define __MULTI_ARRAY_ITERATOR_H

#include <SmallVector.h>
#include <cstddef>

class MultiArrayIterator
{
public:
	MultiArrayIterator();
	MultiArrayIterator(const SmallVector<size_t, 4> &shape_);
	~MultiArrayIterator();

	SmallVector<size_t, 4> shape;
	SmallVector<size_t, 4> indices;
	bool atEnd_;
	void setBegin();
	bool atEnd();
	void next();
	size_t shapeLength(const SmallVector<size_t, 4> &shape_);
};

#endif
