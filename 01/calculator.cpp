#include <iostream>
#include <string>
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
bool get_number(string &str, int &result)
{
	string copy_str = str;
	SkipSpaces(copy_str);

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
		return true;
	}
	return false;
}

// second priority operation
int try_MulDiv(string &str)
{
	int left_result = 0, right_result = 0;
	try
	{
		if (!get_number(str, left_result))
		{
			throw string("Error input string! Expected number in the string.");
		}
	}
	catch (string err)
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
		catch (string err)
		{
			throw err;
		}

		if (op == '*') return left_result * right_result;
		if (op == '/')
		{
			if (right_result == 0) throw string("Error expression! Division by zero.");
			return left_result / right_result;
		}
	}
	return left_result;
}

// third priority operation
int try_AddSub(std::string &str)
{
	int left_result = 0, right_result = 0;
	try
	{
		left_result = try_MulDiv(str);
	}
	catch (string err)
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
				throw string("Error input string! Expected '+' or '-' in the string.");
			}
		}
		catch (string err)
		{
			throw err;
		}
		str = copy_str.substr(1);
		try
		{
			right_result = try_AddSub(str);
		}
		catch (string err)
		{
			throw err;
		}

		if (op == '+') return left_result + right_result;
		if (op == '-') return left_result - right_result;
	}
	return left_result;
}

// caolculate expression in str. log contains error message after calculation (need for testing)
bool calculate(string &str, int &result, string &log)
{
	result = 0;
	try
	{
		result = try_AddSub(str);
		log = "success";
		return true;
	}
	catch (string err)
	{
		log = err;
		return false;
	}
}