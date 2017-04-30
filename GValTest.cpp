#include <GVal.h>
#include <GValSmallVector.h>
#include <GValUtils.h>
#include <GValParser.h>
#include <iostream>
#include <assert.h>
#include <Sutf.h>
#include <math.h>

SUTF_TEST(testGValSmallVector)
{
	GValSmallVector<int, 2> v;
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
}

SUTF_TEST(testGValParseDouble01)
{
	std::string s = "2.0";
	GValParser parser;
	GVal v = parser.parseString(s);
	Sutf::test(v.asDouble() == 2.0);
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

//SUTF_TEST(testGValParser03)
//{
//	std::string s = "MAI(3)[1, 4, 5]";
//	GValParser parser;
//	GVal v = parser.parseString(s);
//	Sutf::test(v[0].asInt() == 1);
//	Sutf::test(v[1].asInt() == 4);
//	Sutf::test(v[2].asInt() == 5);
//}

//SUTF_TEST(testGValParser04)
//{
//	std::string s = "MAD(2, 2)[[1.0, 2.5], [5.25, -2.125]]";
//	GValParser parser;
//	GVal v = parser.parseString(s);
//	Sutf::test(v(0, 0).asDouble() == 1.0);
//	Sutf::test(v(0, 1).asDouble() == 2.5);
//	Sutf::test(v(1, 0).asDouble() == 5.25);
//	Sutf::test(v(1, 1).asDouble() == -2.125);
//}

int main(int argc, char *argv[])
{
	Sutf::runTests(argc, argv);
	//testGValParser001();
	//testGValParser02();
	//testGValParser002();
	return 0;
}
