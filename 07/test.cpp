#include "format.h"

bool test1()
{
	std::string in = "{0}+{1}={2}";
	std::string out = "50+50=100";
	int res = 100;
	try
	{
		if (format(in, 50, 50, res) != out)
			return false;
	}
	catch (const std::runtime_error& err)
	{
		std::cout << err.what() << "\n";
	}
	return true;
}

bool test2()
{
	std::string in = "{0}+{1}-{0}={2}";
	std::string out = "fifty+50-fifty=100";
	std::string x1 = "fifty";
	int res = 100;
	try
	{
		if (format(in, x1, 50, res) != out)
			return false;
	}
	catch (const std::runtime_error& err)
	{
		std::cout << err.what() << "\n";
		return false;
	}
	return true;
}

bool test3()
{
	std::string in = "{0}+{1}-{0}={3}";
	std::string out = "fifty+50-fifty=100";
	std::string x1 = "fifty";
	int res = 100;
	try
	{
		std::string str = format(in, x1, 50, res);
		return false;
	}
	catch (const std::runtime_error& err)
	{
		if (std::string(err.what()) != "Expected more arguments.")
		{
			std::cout << err.what() << "\n";
			return false;
		}
	}
	return true;
}

int main()
{
	if (!test1() || !test2() || !test3())
	{
		std::cout << "Tests failed!\n";
		return 1;
	}
	std::cout << "All tests completed";
	return 0;
}