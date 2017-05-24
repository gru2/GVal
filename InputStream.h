#ifndef __INPUT_STREAM_H
#define __INPUT_STREAM_H

#include <cstddef>

class InputStream
{
public:
	virtual void readBytes(size_t size, char *buffer) = 0;
	virtual bool check() = 0;
	virtual bool atEnd() = 0;
};

#endif
