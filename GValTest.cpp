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
	GVal v;
	v.setBool(true);
	Sutf::test(v.asBool(), "Test set/get true.");
	v.setBool(false);
	Sutf::test(!v.asBool(), "Test set/get false.");
	v.setInt(10);
	Sutf::test(v.asInt() == 10, "Test set/get int.");
	std::cout << "(0)\n";
	v.setMultiArray(3, GVal::GVT_INT);
	std::cout << "(1)\n";
	v.set(0, GVal(10));
	std::cout << "(2)\n";
	v.set(1, GVal(20));
	std::cout << "(3)\n";
	v.set(2, GVal(30));
	std::cout << "(4)\n";
	Sutf::test(v[0].asInt() == 10);
	std::cout << "(5)\n";
	Sutf::test(v[1].asInt() == 20);
	std::cout << "(6)\n";
	Sutf::test(v[2].asInt() == 30);
	std::cout << "(7)\n";
	v.setMap();
	std::cout << "(8)\n";
	v[GVal("pera")] = GVal(23);
	std::cout << "(9)\n";
	Sutf::test(v[GVal("pera")].asInt() == 23);
	std::cout << "(10)\n";
}

int main(int argc, char *argv[])
{
	Sutf::runTests(argc, argv);
	return 0;
}
