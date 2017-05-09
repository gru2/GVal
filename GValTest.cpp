#include <GVal.h>
#include <SmallVector.h>
#include <GValUtils.h>
#include <GValParser.h>
#include <MultiArrayIterator.h>
#include <Sutf.h>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

SUTF_TEST(testSmallVector)
{
	SmallVector<int, 2> v;
	Sutf::test(v.size() == 0);
	v.push_back(12);
	Sutf::test(v.size() == 1);
	Sutf::test(v[0] == 12);
	v.push_back(25);
	Sutf::test(v.size() == 2);
	Sutf::test(v[0] == 12);
	Sutf::test(v[1] == 25);
	v.push_back(77);
	Sutf::test(v.size() == 3);
	Sutf::test(v[0] == 12);
	Sutf::test(v[1] == 25);
	Sutf::test(v[2] == 77);
	v.push_back(373);
	Sutf::test(v.size() == 4);
	Sutf::test(v[0] == 12);
	Sutf::test(v[1] == 25);
	Sutf::test(v[2] == 77);
	Sutf::test(v[3] == 373);
}

SUTF_TEST(testGValUtils)
{
	Sutf::test(toString(GVal("abc")) == "abc");
	Sutf::test(toString(GVal(10)) == "10");
	Sutf::test(toString(GVal(2.5)) == "2.5");
	double ref = 1.234567890123456789;
	std::string s = toString(GVal(ref));
	double test = atof(s.c_str());
	double tol = 1.0e-14;
	Sutf::test(fabs(ref - test) < tol);
}

SUTF_TEST(testGVal)
{
	GVal v;
	v.setBool(true);
	Sutf::test(v.asBool(), "Test set/get true.");
	v.setBool(false);
	Sutf::test(!v.asBool(), "Test set/get false.");
	v.setInt(10);
	Sutf::test(v.asInt() == 10, "Test set/get int.");
	v.setMultiArray(3, GVal::GVT_INT);
	v.set(0, GVal(10));
	v.set(1, GVal(20));
	v.set(2, GVal(30));
	Sutf::test(v[0].asInt() == 10);
	Sutf::test(v[1].asInt() == 20);
	Sutf::test(v[2].asInt() == 30);
	v.setMap();
	v.set(std::string("pera"), GVal(23));
	Sutf::test(v[GVal("pera")].asInt() == 23);
}

SUTF_TEST(testGValParseString)
{
	std::string s = "'foo'";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asString() == "foo");
}

SUTF_TEST(testGValParseInt)
{
	std::string s = "1";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asInt() == 1);
	std::cout << v.asInt() << "\n";
}

SUTF_TEST(testGValParseNegativeInt)
{
	std::string s = "-7";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asInt() == -7);
	std::cout << v.asInt() << "\n";
}

SUTF_TEST(testGValParseDouble01)
{
	std::string s = "2.0";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asDouble() == 2.0);
	std::cout << v.asDouble() << "\n";
}

SUTF_TEST(testGValParseDouble02)
{
	std::string s = "2.0e10";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asDouble() == 2.0e10);
}

SUTF_TEST(testGValParserDouble03)
{
	std::string s = "132.67e-10";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asDouble() == 132.67e-10);
}

SUTF_TEST(testGValParserNegativeDouble)
{
	std::string s = "-0.5e-3";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asDouble() == -0.5e-3);
}

SUTF_TEST(testGValParserNegativeFloat)
{
	std::string s = "-2.25e-7f";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asFloat() == -2.25e-7f);
}

SUTF_TEST(testGValParseTrue)
{
	std::string s = "true";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asBool() == true);
}

SUTF_TEST(testGValParseFalse)
{
	std::string s = "false";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asBool() == false);
}

SUTF_TEST(testGValParseMap)
{
	std::string s =
		"{"
		"	'a' = 'foo';"
		"	'b' = 123;"
		"}";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v["a"].asString() == "foo");
	Sutf::test(v["b"].asInt() == 123);
}

SUTF_TEST(testGValParseList)
{
	std::string s = "[1.5, 'foo', 123]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v[0].asDouble() == 1.5);
	Sutf::test(v[1].asString() == "foo");
	Sutf::test(v[2].asInt() == 123);
}

SUTF_TEST(testMultiArrayIterator01)
{
	MultiArrayIterator it;
	it.shape.push_back(2);
	it.shape.push_back(3);
	it.indices.push_back(0);
	it.indices.push_back(0);
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 0);
	Sutf::test(it.indices[1] == 0);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 0);
	Sutf::test(it.indices[1] == 1);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 0);
	Sutf::test(it.indices[1] == 2);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 1);
	Sutf::test(it.indices[1] == 0);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 1);
	Sutf::test(it.indices[1] == 1);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 1);
	Sutf::test(it.indices[1] == 2);
	it.next();
	Sutf::test(it.atEnd() == true);
}

SUTF_TEST(testMultiArrayIterator02)
{
	SmallVector<size_t, 4> shape;
	shape.push_back(3);
	MultiArrayIterator it(shape);

	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 0);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 1);
	it.next();
	Sutf::test(it.atEnd() == false);
	Sutf::test(it.indices[0] == 2);
	it.next();
	Sutf::test(it.atEnd() == true);
}

SUTF_TEST(testGValParser03)
{
	std::string s = "MAI(3)[1, 4, 5]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.size() == 3);
	Sutf::test(v[0].asInt() == 1);
	Sutf::test(v[1].asInt() == 4);
	Sutf::test(v[2].asInt() == 5);
}

SUTF_TEST(testGValParser031)
{
	std::string s = "MAI(2,3)[[1, 4, 5],[14, 48, 51]]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.numberOfDimensions() == 2);
	Sutf::test(v.size(0) == 2);
	Sutf::test(v.size(1) == 3);
	Sutf::test(v(0, 0).asInt() == 1);
	Sutf::test(v(0, 1).asInt() == 4);
	Sutf::test(v(0, 2).asInt() == 5);
	Sutf::test(v(1, 0).asInt() == 14);
	Sutf::test(v(1, 1).asInt() == 48);
	Sutf::test(v(1, 2).asInt() == 51);
}

SUTF_TEST(testGValParser04)
{
	std::string s = "MAD(2, 2)[[1.0, 2.5], [5.25, -2.125]]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v(0, 0).asDouble() == 1.0);
	Sutf::test(v(0, 1).asDouble() == 2.5);
	Sutf::test(v(1, 0).asDouble() == 5.25);
	Sutf::test(v(1, 1).asDouble() == -2.125);
}

SUTF_TEST(testGValParser05)
{
	std::string s = "MAF(2, 1)[[1.0f], [15.5f]]";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v(0, 0).asFloat() == 1.0f);
	Sutf::test(v(1, 0).asFloat() == 15.5f);
}

SUTF_TEST(testGValParser06)
{
	std::string s = "MAG(3)[1.5f, 2, 'pera']";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v[0].asFloat() == 1.5f);
	Sutf::test(v[1].asInt() == 2);
	Sutf::test(v[2].asString() == "pera");
}

int main(int argc, char *argv[])
{
	Sutf::runTests(argc, argv);
	//testGValParser031();
	return 0;
}
