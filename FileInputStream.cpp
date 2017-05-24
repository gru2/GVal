#include "FileInputStream.h"

FileInputStream::FileInputStream()
{
	file = 0;
	position = 0;
	fileSize = 0;
}

FileInputStream::FileInputStream(const std::string &fileName)
{
	open(fileName);
}

FileInputStream::~FileInputStream()
{
	close();
}

void FileInputStream::open(const std::string &fileName)
{
	file = fopen(fileName.c_str(), "rb");
	fileSize = getFileSize();
	position = 0;
}

void FileInputStream::close()
{
	if (file)
	{
		fclose(file);
		file = 0;
		position = 0;
		fileSize = 0;
	}
}

size_t FileInputStream::getFileSize()
{
	size_t oldPosition = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_t fs = ftell(file);
	fseek(file, oldPosition, SEEK_SET);
	return fs;
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
