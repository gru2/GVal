#include <BinaryStream.h>
#include <Stream.h>

BinaryStream::BinaryStream(Stream *s) : stream(s) { }

unsigned char BinaryStream::readByte()
{
	char x;
	stream->readBytes(1, &x);
	return (unsigned char)x;
}

char BinaryStream::readChar()
{
	char x;
	stream->readBytes(1, &x);
	return x;
}

short BinaryStream::readShort()
{
	short x;
	stream->readBytes(2, (char *)&x);
	return x;
}

int BinaryStream::readInt()
{
	int x;
	stream->readBytes(4, (char *)&x);
	return x;
}

long long BinaryStream::readLong()
{
	long long x;
	stream->readBytes(8, (char *)&x);
	return x;
}

float BinaryStream::readFloat()
{
	float x;
	stream->readBytes(4, (char *)&x);
	return x;
}

double BinaryStream::readDouble()
{
	double x;
	stream->readBytes(8, (char *)&x);
	return x;
}

std::string BinaryStream::readString()
{
	long long len = readLong();
	std::string x((size_t)len, ' ');
	stream->readBytes((size_t)len, &x[0]);
	return x;
}

void BinaryStream::writeByte(unsigned char x)
{
	stream->writeBytes(1, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeChar(char x)
{
	stream->writeBytes(1, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeShort(short x)
{
	stream->writeBytes(2, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeInt(int x)
{
	stream->writeBytes(4, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeLong(long long x)
{
	stream->writeBytes(8, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeFloat(float x)
{
	stream->writeBytes(4, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeDouble(double x)
{
	stream->writeBytes(8, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeString(const std::string &x)
{
	long long n = (long long)x.size();
	writeLong(n);
	stream->writeBytes((size_t)n, &x[0]);
}
