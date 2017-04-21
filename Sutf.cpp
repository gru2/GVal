#include <Sutf.h>
#include <iostream>

using namespace Sutf;

int failCount = 0;

Initializer *Initializer::tests = 0;

Initializer::Initializer(TestType x, const std::string &name)
{
	test = x;
	nextTest = tests;
	tests = this;
	testName = name;
}

Initializer *Initializer::getTests()
{
	return tests;
}

void Sutf::test(bool result)
{
	if (!result)
	{
		std::cout << "FAILED\n";
		failCount++;
	}
}

void Sutf::test(bool result, const std::string &msg)
{
	if (!result)
	{
		std::cout << "FAILED " + msg + "\n";
		failCount++;
	}
}

int Sutf::runTests(int argc, char *argv[])
{
	Sutf::Initializer *p = Sutf::Initializer::getTests();
	for (;;)
	{
		if (!p)
			break;
		int oldFailCount = failCount;
		TestType test = p->getTest();
		test();
		if (failCount == oldFailCount)
			std::cout << "TEST PASSED " + p->getTestName() << "\n";
		else
			std::cout << "TEST FAILED " + p->getTestName() << "\n";
		p = p->getNextTest();
	}

	std::cout << "Total fail count is " << failCount << ".\n";

	if (failCount == 0)
		return 0;

	return 1;
}
