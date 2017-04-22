#include <GVal.h>
#include <GValSmallVector.h>
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

SUTF_TEST(testGVal)
{
	GVal val;
	val.setBool(true);
	Sutf::test(val.asBool(), "Test set/get true.");
	val.setBool(false);
	Sutf::test(!val.asBool(), "Test set/get false.");
	val.setInt(10);
	Sutf::test(val.asInt() == 10, "Test set/get int.");
}

int main(int argc, char *argv[])
{
	Sutf::runTests(argc, argv);
	return 0;
}
