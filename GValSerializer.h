#ifndef __GVAL_SERIALIZER_H
#define __GVAL_SERIALIZER_H

#include <GVal.h>

class BinaryStream;

class GValSerialzier
{
public:
	GValSerialzier();

	void write(const GVal &x);
	GVal read();

	BinaryStream *binaryStream;
};

#endif
