#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <stdlib.h>

std::string format_sub(const std::string &str, const std::vector<std::string> &strs)
{
	std::string res;
	std::string digit;
	bool open_bracket = false;
	for (int i = 0; i < static_cast<int>(str.size()); ++i)
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

template<typename Arg, typename ... Args>
std::string format_sub(const std::string& str, std::vector<std::string>& strs, Arg&& arg, Args&& ... args)
{
	std::stringstream ss;
	ss << (std::forward<Arg>(arg));
	strs.push_back(ss.str());
	return format_sub(str, strs, std::forward<Args>(args) ...);
}

template<typename Arg, typename ... Args>
std::string format(const std::string& str, Arg&& arg, Args&& ... args)
{
	std::vector<std::string> strs;
	return format_sub(str, strs, std::forward<Arg>(arg), std::forward<Args>(args) ...);
}
