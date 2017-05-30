#include <MemoryStream.h>
#include <algorithm>

MemoryStream::MemoryStream()
{
	position = 0;
}

void MemoryStream::reset()
{
	position = 0;
	buffer.clear();
}

void MemoryStream::writeBytes(size_t size, const char *data)
{
	size_t n = buffer.size();
	buffer.resize(n + size);
	for (size_t i = 0; i < size; i++)
		buffer[n + i] = data[i];
}

void MemoryStream::readBytes(size_t size, char *data)
{
	if (position >= buffer.size())
	{
		position += size;
		return;
	}
	size_t n = std::min<size_t>(size, buffer.size() - position);
	for (int i = 0; i < n; i++)
		data[i] = buffer[position + i];
	position += size;
}

bool MemoryStream::check()
{
	if (position > buffer.size())
		return false;
	return true;
}

bool MemoryStream::atEnd()
{
	if (position < buffer.size())
		return false;
	return true;
}
