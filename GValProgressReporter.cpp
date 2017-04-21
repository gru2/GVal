#include <GValProgressReporter.h>
#include <stdio.h>
#include <stdlib.h>

void GValProgressReporter::error(const std::string &msg) const
{
	printf("error:%s\n", msg.c_str());
	exit(1);
}
