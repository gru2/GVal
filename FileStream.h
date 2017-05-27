#ifndef __FILE_STREAM_H
#define __FILE_STREAM_H

#include <Stream.h>
#include <string>
#include <stdio.h>
#include <ProgressReporter.h>

class FileStream : public Stream
{
public:
	enum ModeType { READ_MODE, WRITE_MODE };

	FileStream();
	FileStream(const std::string &fileName, ModeType mode_);
	~FileStream();

	void open(const std::string &fileName, ModeType mode_);
	void close();
	size_t getFileSize();

	virtual void writeBytes(size_t size, char *buffer);
	virtual void readBytes(size_t size, char *buffer);
	virtual bool check();
	virtual bool atEnd();

protected:
	ModeType mode;
	FILE *file;
	size_t fileSize;
	size_t position;
	ProgressReporter progressReporter;
};

#endif
