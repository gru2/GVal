#ifndef __FILE_INPUT_STREAM_H
#define __FILE_INPUT_STREAM_H

#include <InputStream.h>
#include <string>
#include <stdio.h>
#include <ProgressReporter.h>

class FileInputStream
{
public:
	FileInputStream();
	FileInputStream(const std::string &fileName);
	~FileInputStream();

	void open(const std::string &fileName);

	virtual void readBytes(size_t size, char *buffer);
	virtual bool check();
	virtual bool atEnd();

	FILE *file;
	size_t fileSize;
	size_t position;
};

#endif
