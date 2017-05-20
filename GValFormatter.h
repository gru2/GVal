#ifndef __GVAL_FORMATTER_1_H
#define __GVAL_FORMATTER_1_H

#include <string>
#include <SmallVector.h>

class GVal;
class MultiArraySlice;

class GValFormatter
{
public:
	std::string toStringSimple(const GVal &x);
	std::string toStringSimpleMultiArray(const GVal &x);
	std::string toStringSimpleMap(const GVal &x);
	std::string toStringSimpleMultiArrayRecursive(const GVal &x, const MultiArraySlice &slice);
	std::string generateMultiArrayHeader(const SmallVector<size_t, 4> &shape, int entryType);
};

#endif
