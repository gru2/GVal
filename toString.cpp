#include <sstream>
#include <iomanip>
#include <toString.h>

template <typename T>
std::string toStringWithPrecision(const T x, const int n = 19)
{
	std::ostringstream out;
	out << std::setprecision(n) << x;
	return out.str();
}

std::string toString(int x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

std::string toString(long long x)
{
	std::ostringstream out;
	out << x;
	return out.str();
}

std::string toString(float x, const int n)
{
	return toStringWithPrecision<float>(x);
}

std::string toString(double x, const int n)
{
	return toStringWithPrecision<double>(x);
}
