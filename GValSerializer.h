#ifndef __GVAL_SERIALIZER_H
#define __GVAL_SERIALIZER_H

#include <GVal.h>
#include <ProgressReporter.h>

class BinaryStream;

class GValSerialzier
{
public:
	GValSerialzier();

	void write(const GVal &x);
	GVal read();
	GVal readMultiArray();
	GVal readMap();

	void writeMultiArray(const GVal &x);
	void writeMap(const GVal &x);
	BinaryStream *binaryStream;
	ProgressReporter progressReporter;
};

#endif
