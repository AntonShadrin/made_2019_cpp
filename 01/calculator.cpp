#include <iostream>
#include <string>
#include <exception>
using namespace std;

void SkipSpaces(string &str)
{
	int indx = 0;
	while (indx < str.size() && str[indx] == ' ')
	{
		++indx;
	}
	str = str.substr(indx);
}

// first priority operation
int get_number(string &str)
{
	string copy_str = str;
	SkipSpaces(copy_str);

	int result = 0;
	int indx = 0;
	int sign = 1;
	if (copy_str.size() > 0 && copy_str[0] == '-')
	{
		sign = -1;
		copy_str = copy_str.substr(1);
	}
	if (copy_str.size() > 0 && isdigit(copy_str[0]))
	{
		while (indx < copy_str.size() && isdigit(copy_str[indx]))
		{
			++indx;
		}
		result = std::stoi(copy_str.substr(0, indx));
		result *= sign;
		str = copy_str.substr(indx);
		return result;
	}
	throw invalid_argument("Error input string! Expected number in the string.");
}

// second priority operation
int try_MulDiv(string &str)
{
	int left_result = 0, right_result = 0;
	try
	{
		left_result = get_number(str);
	}
	catch (invalid_argument& err)
	{
		throw err;
	}

	while (true)
	{
		string copy_str = str;
		SkipSpaces(copy_str);
		if (copy_str.empty())
		{
			return left_result;
		}
		char op = copy_str[0];
		if (op != '*' && op != '/')
		{
			return left_result;
		}

		str = copy_str.substr(1);
		try
		{
			right_result = try_MulDiv(str);
		}
		catch (invalid_argument& err)
		{
			throw err;
		}

		if (op == '*') return left_result * right_result;
		if (op == '/')
		{
			if (right_result == 0) throw invalid_argument("Error expression! Division by zero.");
			return left_result / right_result;
		}
	}
	return left_result;
}

// third priority operation
int try_AddSub(string &str)
{
	int left_result = 0, right_result = 0;
	try
	{
		left_result = try_MulDiv(str);
	}
	catch (invalid_argument& err)
	{
		throw err;
	}
	while (true)
	{
		string copy_str = str;
		SkipSpaces(copy_str);
		if (copy_str.empty())
		{
			return left_result;
		}
		char op = copy_str[0];
		try
		{
			if (op != '+' && op != '-')
			{
				throw invalid_argument("Error input string! Expected '+' or '-' in the string.");
			}
		}
		catch (invalid_argument& err)
		{
			throw err;
		}
		str = copy_str.substr(1);
		try
		{
			right_result = try_AddSub(str);
		}
		catch (invalid_argument err)
		{
			throw err;
		}

		if (op == '+') return left_result + right_result;
		if (op == '-') return left_result - right_result;
	}
	return left_result;
}

// caolculate expression in str
int calculate(string const & str)
{
	string copy_str = str;
	int result = 0;
	try
	{
		result = try_AddSub(copy_str);
		return result;
	}
	catch (invalid_argument& err)
	{
		throw err;
	}
}