#include <GValUtils.h>
#include <toString.h>

std::string toString(const GVal &x)
{
	int type = x.getType();
	switch (type)
	{
		case GVal::GVT_NULL:
			return "null";
		case GVal::GVT_BOOL:
		{
			bool v = x.asBool();
			if (v)
				return "true";
			else
				return "false";
		}
		case GVal::GVT_INT:
		{
			int v = x.asInt();
			return toString(v);
		}
		case GVal::GVT_LONG:
		{
			long long v = x.asLong();
			return toString(v);
		}
		case GVal::GVT_FLOAT:
		{
			float v = x.asFloat();
			return toString(v);
		}
		case GVal::GVT_DOUBLE:
		{
			double v = x.asDouble();
			return toString(v);
		}
		case GVal::GVT_STRING:
			return x.asString();
		case GVal::GVT_MULTI_ARRAY:
			return "TODO"; // TODO
		case GVal::GVT_MAP:
			return "TODO"; // TODO
		case GVal::GVT_GENERIC:
			return "GENERIC";
		default:
			return "TODO"; // TODO
		break;
	}
}
