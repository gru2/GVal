#include <BinaryStream.h>
#include <Stream.h>

BinaryStream::BinaryStream(Stream *s) : stream(s) { }

unsigned char BinaryStream::readByte()
{
	char x;
	stream->readBytes(1, &x);
	return x;
}

int BinaryStream::readInt()
{
	int x;
	stream->readBytes(4, (char *)&x);
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

void BinaryStream::writeByte(unsigned char x)
{
	stream->writeBytes(1, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeInt(int x)
{
	stream->writeBytes(4, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeFloat(float x)
{
	stream->writeBytes(4, reinterpret_cast<char *>(&x));
}

void BinaryStream::writeDouble(double x)
{
	stream->writeBytes(8, reinterpret_cast<char *>(&x));
}
