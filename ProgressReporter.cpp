#include <ProgressReporter.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

void ProgressReporter::error(const std::string &msg) const
{
#if GVAL_THROWS
	throw std::runtime_error(msg);
#else
	printf("error:%s\n", msg.c_str());
	exit(1);
#endif
}

void ProgressReporter::warning(const std::string &msg) const
{
	printf("warning:%s\n", msg.c_str());
}
