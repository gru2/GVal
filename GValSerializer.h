#ifndef __GVAL_SERIALIZER_H
#define __GVAL_SERIALIZER_H

class GValSerialzier
{
public:
	GValSerialzier();

	void write(const GVal &x);
	GVal read();

	BinaryStream *binayStream;
};

#endif
