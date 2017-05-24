#include "FileInputStream.h"

FileInputStream::FileInputStream()
{
	file = 0;
}

FileInputStream::FileInputStream(const std::string &fileName)
{
}

FileInputStream::~FileInputStream()
{
}

void FileInputStream::open(const std::string &fileName)
{
	file = fopen(fileName.c_str(), "rb");
}

void FileInputStream::readBytes(size_t size, char *buffer)
{
	position += size;
	fread(buffer, 1, size, file);
}

bool FileInputStream::check()
{
	if (file == 0)
		return false;
	if (position > fileSize)
		return false;
	return true;
}

bool FileInputStream::atEnd()
{
	if (position < fileSize)
		return false;
	return true;
}
