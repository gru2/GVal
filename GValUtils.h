#ifndef __GVAL_UTILS_H
#define __GVAL_UTILS_H

#include <string>
#include <GVal.h>

std::string toString(const GVal &x);
GVal gvalToMultiArray(const GVal &u, const SmallVector<size_t, 4> &shape, GVal::GValType type);

class GValToStringFormater
{
};

#endif
