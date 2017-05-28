#ifndef __MEMORY_STREAM_H
#define __MEMORY_STREAM_H

#include <Stream.h>
#include <vector>

class MemoryStream : public Stream
{
public:
	MemoryStream();

	void reset();

	virtual void writeBytes(size_t size, const char *buffer);
	virtual void readBytes(size_t size, char *buffer);
	virtual bool check();
	virtual bool atEnd();

	std::vector<char> buffer;
	size_t position;
};

#endif
