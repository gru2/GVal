#include <GVal.h>
#include <GValSmallVector.h>
#include <GValUtils.h>
#include <iostream>
#include <assert.h>
#include <Sutf.h>

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
	Sutf::test(std::abs(ref - test) < tol);
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

int main(int argc, char *argv[])
{
	Sutf::runTests(argc, argv);
	return 0;
}
