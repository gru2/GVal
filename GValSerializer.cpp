#include <GValSerializer.h>
#include <BinaryStream.h>

GValSerialzier::GValSerialzier()
{
	binaryStream = 0;
}

void GValSerialzier::write(const GVal &x)
{
	BinaryStream &bs = *binaryStream;
	int type = x.getType();
	bs.writeInt(type);
	switch (type) {
	case GVal::GVT_NULL:
		break;
	case GVal::GVT_BOOL:
		bs.writeInt(x.asBool());
		break;
	case GVal::GVT_INT:
		bs.writeInt(x.asInt());
		break;
	case GVal::GVT_LONG:
		bs.writeLong(x.asLong());
		break;
	case GVal::GVT_FLOAT:
		bs.writeFloat(x.asFloat());
		break;
	case GVal::GVT_DOUBLE:
		bs.writeDouble(x.asDouble());
		break;
	case GVal::GVT_STRING:

		break;
	default:
		progressReporter.error("GValSerialzier::write bad GVal type "
		+ toString(type));
	}
}

GVal GValSerialzier::read()
{

}
