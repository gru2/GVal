#include <GValFormatter.h>
#include <toString.h>
#include <GVal.h>
#include <MultiArraySlice.h>

std::string GValFormatter::toStringSimple(const GVal &x)
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
		return "'" + x.asString() + "'";
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

std::string GValFormatter::toStringSimpleMultiArray(const GVal &x)
{
	if (x.getType() != GVal::GVT_MULTI_ARRAY)
		return "not multi array";
	const std::shared_ptr<void> genericValue = x.getGenericValue();
	GValMultiArray *ma = static_cast<GValMultiArray *>(genericValue.get());
	const SmallVector<size_t, 4> &shape = ma->getShape();
	MultiArraySlice slice;
	slice.setWholeArray(shape);
	std::string r;
	int entryType = ma->getEntryType();
	if (entryType != GVal::GVT_GENERIC || shape.size() != 1)
		r = generateMultiArrayHeader(shape, entryType);
	r += toStringSimpleMultiArrayRecursive(x, slice);
	return r;
}

std::string GValFormatter::toStringSimpleMap(const GVal &x)
{
	return std::string();
}

std::string GValFormatter::toStringSimpleMultiArrayRecursive(const GVal &x,
const MultiArraySlice &slice)
{
	std::string r = "[";
	size_t m = slice.shape[0];
	int n = slice.shape.size();
	for (size_t i = 0; i < m; i++)
	{
		if (n <= 1)
		{
			SmallVector<size_t, 4> indices;
			indices.push_back(i);
			size_t offset = slice.calculateOffset(indices);
			GVal v = x[offset];
			std::string s = toStringSimple(v);
			r += s;
		}
		else
		{
			MultiArraySlice newSlice = slice.slice(0, i);
			std::string s = toStringSimpleMultiArrayRecursive(x, newSlice);
			r += s;
		}
		if (i < m - 1)
			r += ", ";
	}
	r += "]";
	return r;
}

std::string GValFormatter::generateMultiArrayHeader(
const SmallVector<size_t, 4> &shape, int entryType)
{
	std::string r;
	switch (entryType)
	{
	case GVal::GVT_INT:
		r = "MAI";
		break;
	case GVal::GVT_FLOAT:
		r = "MAF";
		break;
	case GVal::GVT_DOUBLE:
		r = "MAD";
		break;
	case GVal::GVT_GENERIC:
		r = "MAG";
		break;
	default:
		r = "unknown multi array type";
	}
	r += "(";
	int n = (int)shape.size();
	for (int i = 0; i < n; i++)
	{
		r += toString((long long)shape[i]);
		if (i < n - 1)
			r += ", ";
	}
	r += ")";
	return r;
}
