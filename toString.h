#ifndef __TO_STRING_H
#define __TO_STRING_H

#include <string>

std::string toString(int x);
std::string toString(long long x);
std::string toString(float x, const int n = 10);
std::string toString(double x, const int n = 19);

#endif
