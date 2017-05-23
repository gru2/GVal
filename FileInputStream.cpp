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
}

void FileInputStream::readBytes(size_t size, char * buffer)
{
}

bool FileInputStream::check()
{
	return false;
}

bool FileInputStream::atEnd()
{
	return false;
}
