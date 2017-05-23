#ifndef __PROGRESS_REPORTER_H
#define __PROGRESS_REPORTER_H

#include <string>

class ProgressReporter
{
public:
	void error(const std::string &msg) const;
	void warning(const std::string &msg) const;
};

#endif
