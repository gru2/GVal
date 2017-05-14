#include <GValFormatter.h>
#include <toString.h>
#include <GVal.h>
#include <MultiArraySlice.h>

std::string GValFromatter::toStringSimple(const GVal &x)
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
		return toStringSimpleMultiArray(x);
	case GVal::GVT_MAP:
		return toStringSimpleMap(x);
	case GVal::GVT_GENERIC:
		return "GENERIC";
	default:
		return "TODO"; // TODO
		break;
	}
}

std::string GValFromatter::toStringSimpleMultiArray(const GVal &x)
{
	if (x.getType() != GVal::GVT_MULTI_ARRAY)
		return "not multi array";
	GValMultiArray *ma = static_cast<GValMultiArray *>(genericValue.get());
	const SmallVector<size_t, 4> &shape = ma->getShape();
	MultiArraySlice slice;
	slice.setWholeArray(shape);
	std::string r = toStringSimpleMultiArrayRecursive(x, slice);
}

std::string GValFromatter::toStringSimpleMultiArrayRecursive(const GVal &x, const MultiArraySlice &slice)
{
	std::string r = "[";
	size_t m = slice.shape[0];
	int n = slice.shape.size();
	for (size_t i = 0; i < m; i++)
	{
		if (n <= 1)
		{
			size_t offset = slice.calculateOffset(i);
			GVal v = x[offset];
			std::string s = toStringSimple(v);
			r += s;
		}
		else
		{
			MultiArraySlice newSlice = slice.slice(0, i);
			std::string s = toStringSimpleMultiArrayRecursive(x, newSlice);
		}
		if (i != m - 1)
			r += ", ";
	}
	return r;
}
