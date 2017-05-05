#ifndef __MULTI_ARRAY_ITERATOR_H
#define __MULTI_ARRAY_ITERATOR_H

#include <SmallVector.h>

class MultiArrayIterator
{
public:
	MultiArrayIterator();
	MultiArrayIterator(const SmallVector<size_t, 4> &shape_);
	~MultiArrayIterator();

	SmallVector<size_t, 4> shape;
	SmallVector<size_t, 4> indices;
	void setBegin();
	bool atEnd();
	void next();
};

#endif
