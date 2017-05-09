#include <GValUtils.h>
#include <toString.h>
#include <MultiArrayIterator.h>
#include <iostream>

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

GVal gvalToMultiArray(const GVal &u, const SmallVector<size_t, 4> &shape, GVal::GValType type)
{
	std::cout << "gvalToMultiArray entering...\n";
	GVal v;
	v.setMultiArray(shape, type);
	MultiArrayIterator it(shape);
	unsigned n = it.shape.size();
	std::cout << "n = " << n << "\n";
	std::cout << "shape[0] = " << shape[0] << "\n";
	if (shape.size() > 1)
		std::cout << "shape[1] = " << shape[1] << "\n";
	for (; !it.atEnd(); it.next())
	{
		std::cout << "------ ";
		GVal t = u;
		for (unsigned i = 0; i < n; i++)
		{
			size_t index = it.indices[i];
			t = t[index];
		}

		v.set(it.indices, t);
		std::cout << toString(t) << "\n";
	}
	return v;
}
