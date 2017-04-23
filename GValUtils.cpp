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
		{
			long long v = x.asLong();
			return std::to_string(v);
		}
		case GVal::GVT_FLOAT:
		{
			float v = x.asLong();
			return std::to_string(v);
		}
		case GVal::GVT_DOUBLE:
		{
			double v = x.asLong();
			return std::to_string(v);
		}
		case GVal::GVT_STRING:
			return x.asString();
		case GVal::GVT_MULTI_ARRAY:
		case GVal::GVT_MAP:
		case GVal::GVT_GENERIC:
		default:
			return "TODO"; // TODO
		break;
	}
}
