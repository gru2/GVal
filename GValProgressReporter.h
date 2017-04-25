#ifndef __GVAL_PROGRESS_REPORTER_H
#define __GVAL_PROGRESS_REPORTER_H

#include <string>

class GValProgressReporter
{
public:
	void error(const std::string &msg) const;
	void warning(const std::string &msg) const;
};

#endif
