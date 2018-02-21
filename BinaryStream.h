#ifndef __BINARY_STREAM_H
#define __BINARY_STREAM_H

#include <string>

class Stream;

class BinaryStream
{
public:
	BinaryStream(Stream *s);

	unsigned char readByte();
	char readChar();
	short readShort();
	int readInt();
	long long readLong();
	float readFloat();
	double readDouble();
	std::string readString();

	void writeByte(unsigned char x);
	void writeChar(char x);
	void writeShort(short x);
	void writeInt(int x);
	void writeLong(long long x);
	void writeFloat(float x);
	void writeDouble(double x);
	void writeString(const std::string &x);

	Stream *stream;
};

#endif
