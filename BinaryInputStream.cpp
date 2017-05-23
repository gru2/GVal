#include "BinaryInputStream.h"
#include "InputStream.h"

unsigned char BinaryInputStream::readByte()
{
	char x;
	inputStream->readBytes(1, &x);
	return x;
}

int BinaryInputStream::readInt()
{
	int x;
	inputStream->readBytes(4, (char *)&x);
	return x;
}

float BinaryInputStream::readFloat()
{
	float x;
	inputStream->readBytes(4, (char *)&x);
	return x;
}

double BinaryInputStream::readDouble()
{
	double x;
	inputStream->readBytes(8, (char *)&x);
	return x;
}
