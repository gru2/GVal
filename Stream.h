#ifndef __STREAM_H
#define __STREAM_H

#include <cstddef>

class Stream
{
public:
	virtual void writeBytes(size_t size, const char *buffer) = 0;
	virtual void readBytes(size_t size, char *buffer) = 0;
	virtual bool check() = 0;
	virtual bool atEnd() = 0;
};

#endif
