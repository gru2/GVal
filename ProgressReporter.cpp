#include <ProgressReporter.h>
#include <stdio.h>
#include <stdlib.h>

void ProgressReporter::error(const std::string &msg) const
{
	printf("error:%s\n", msg.c_str());
	exit(1);
}

void ProgressReporter::warning(const std::string &msg) const
{
	printf("warning:%s\n", msg.c_str());
}
