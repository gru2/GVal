#include <FileStream.h>

FileStream::FileStream()
{
	mode = READ_MODE;
	file = 0;
	position = 0;
	fileSize = 0;
}

FileStream::FileStream(const std::string &fileName, FileStream::ModeType mode_)
{
	open(fileName, mode_);
}

FileStream::~FileStream()
{
	close();
}

void FileStream::open(const std::string &fileName, ModeType mode_)
{
	close();
	mode = mode_;
	if (mode == READ_MODE)
	{
		file = fopen(fileName.c_str(), "rb");
		fileSize = getFileSize();
		position = 0;
		return;
	}
	if (mode == WRITE_MODE)
	{
		file = fopen(fileName.c_str(), "wb");
		fileSize = 0;
		position = 0;
		return;
	}
	progressReporter.error("FileStream::open:Internal error.");
}

void FileStream::close()
{
	if (file)
	{
		fclose(file);
		mode = READ_MODE;
		file = 0;
		position = 0;
		fileSize = 0;
	}
}

size_t FileStream::getFileSize()
{
	size_t oldPosition = ftell(file);
	fseek(file, 0L, SEEK_END);
	size_t fs = ftell(file);
	fseek(file, oldPosition, SEEK_SET);
	return fs;
}

void FileStream::writeBytes(size_t size, char *buffer)
{
	position += size;
	fwrite(buffer, 1, size, file);
}

void FileStream::readBytes(size_t size, char *buffer)
{
	position += size;
	fread(buffer, 1, size, file);
}

bool FileStream::check()
{
	if (file == 0)
		return false;
	if (mode == READ_MODE && position > fileSize)
		return false;
	return true;
}

bool FileStream::atEnd()
{
	if (position < fileSize)
		return false;
	return true;
}
