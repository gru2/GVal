#ifndef __GVAL_UTILS_H
#define __GVAL_UTILS_H

#include <string>
#include <GVal.h>

std::string toString(const GVal &x);
GVal gvalToMultiArray(const GVal &u, const SmallVector<size_t, 4> &shape, GVal::GValType type);
GVal gvParseFile(const std::string &fileName);
void gvWriteTextFile(const GVal &x, const std::string &fileName);
GVal gvReadFromBinaryFile(const std::string &fileName);
void gvWriteToBinaryFile(const GVal &x, const std::string &fileName);
GVal gvArray();
GVal gvArray(const GVal &x0);
GVal gvArray(const GVal &x0, const GVal &x1);
GVal gvArray(const GVal &x0, const GVal &x1, const GVal &x2);
#endif
