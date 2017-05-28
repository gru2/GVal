#ifndef __BINARY_STREAM_H
#define __BINARY_STREAM_H

class Stream;

class BinaryStream
{
public:
	BinaryStream(Stream *s);

	unsigned char readByte();
	int readInt();
	long long readLong();
	float readFloat();
	double readDouble();

	void writeByte(unsigned char x);
	void writeInt(int x);
	void writeLong(long long x);
	void writeFloat(float x);
	void writeDouble(double x);

	Stream *stream;
};

#endif
