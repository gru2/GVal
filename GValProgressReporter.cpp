#include <GValProgressReporter.h>
#include <stdio.h>
#include <stdlib.h>

void GValProgressReporter::error(const std::string &msg) const
{
	printf("error:%s\n", msg.c_str());
	exit(1);
}

void GValProgressReporter::warning(const std::string &msg) const
{
	printf("warning:%s\n", msg.c_str());
}
