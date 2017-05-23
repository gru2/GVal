#ifndef __BINARY_INPUT_STREAM_H
#define __BINARY_INPUT_STREAM_H

class InputStream;

class BinaryInputStream
{
public:
	unsigned char readByte();
	int readInt();
	float readFloat();
	double readDouble();
	InputStream *inputStream;
};

#endif
