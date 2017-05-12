#ifndef __GVAL_FORMATTER_H
#define __GVAL_FORMATTER_H

#include <string>

class GValFromatter
{
public:
	std::string toStringSimple(const GVal &x);
	std::string toStringSimpleMultiArray(const GVal &x);
	std::string toStringSimpleMap(const GVal &x);
};

#endif
