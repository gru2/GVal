#include <GValUtils.h>

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
			return std::to_string(v);
		}
		case GVal::GVT_LONG:
		case GVal::GVT_FLOAT:
		case GVal::GVT_DOUBLE:
		case GVal::GVT_STRING:
		case GVal::GVT_MULTI_ARRAY:
		case GVal::GVT_MAP:
		case GVal::GVT_GENERIC:
		default:
		break;
	}
}
