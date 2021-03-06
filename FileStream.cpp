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
	mode = READ_MODE;
	file = 0;
	position = 0;
	fileSize = 0;
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
		if (file == 0)
		{
			progressReporter.error("unable to open file '" + fileName +"' for reading.");
			return;
		}
		fileSize = getFileSize();
		position = 0;
		return;
	}
	if (mode == WRITE_MODE)
	{
		file = fopen(fileName.c_str(), "wb");
		if (file == 0)
		{
			progressReporter.error("unable to open file '" + fileName +"' for writing.");
			return;
		}
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
	size_t oldPosition = (size_t)ftell(file);
	fseek(file, 0L, SEEK_END);
	size_t fs = (size_t)ftell(file);
	fseek(file, (long)oldPosition, SEEK_SET);
	return fs;
}

void FileStream::writeBytes(size_t size, const char *buffer)
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
