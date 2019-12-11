#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <stdlib.h>

template<typename Arg>
void format_sub(std::vector<std::string>& strs, Arg&& arg)
{
	std::stringstream ss;
	ss << (std::forward<Arg>(arg));
	strs.push_back(ss.str());
}

template<typename Arg, typename ... Args>
void format_sub(std::vector<std::string>& strs, Arg&& arg, Args&& ... args)
{
	std::stringstream ss;
	ss << (std::forward<Arg>(arg));
	strs.push_back(ss.str());
	format_sub(strs, std::forward<Args>(args) ...);
}

template<typename Arg, typename ... Args>
std::string format(const std::string& str, Arg&& arg, Args&& ... args)
{
	// argument promotion
	std::vector<std::string> strs;
	format_sub(strs, std::forward<Arg>(arg), std::forward<Args>(args) ...);

	// formatting string
	std::string res;
	std::string digit;
	bool open_bracket = false;
	for (size_t i = 0; i < str.size(); ++i)
	{
		char ch = str[i];
		if (open_bracket)
		{
			if (isdigit(ch))
			{
				digit += ch;
			}
			else
			{
				if (ch == '}' && !digit.empty())
				{
					int num = atoi(digit.c_str());
					if (num < static_cast<int>(strs.size()))
					{
						res += strs[num];
					}
					else
					{
						throw std::runtime_error("Expected more arguments.");
					}
					digit.clear();
					open_bracket = false;
				}
				else
				{
					throw std::runtime_error("Expected number in brackets {...}.");
				}
			}
		}
		else
		{
			if (ch == '{')
			{
				open_bracket = true;
			}
			else
			{
				res += ch;
			}
		}
	}
	if (open_bracket)
		throw std::runtime_error("Expected closed bracket }.");

	return res;
}



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