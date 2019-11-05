#include <iostream>
using namespace std;
#include "calculator.h"

string log_success("success");
string log_error_number("Error input string! Expected number in the string.");
string log_error_operator("Error input string! Expected '+' or '-' in the string.");
string log_error_division_by_zero("Error expression! Division by zero.");

// testing invalid expression
bool test_invalid_string()
{
	int result = 0;
	string test1(" 1 + 1 -/ 2");
	string test2("--1");
	string test3("");
	string test4("abc");
	string test5("1 % 2");
	string test6("1 +2 plus 3");
	try
	{
		result = calculate(test1);
		cout << "test_invalid_string FAILED! test1\n";
		return false;
	}
	catch (const invalid_argument err)
	{
		if (err.what() != log_error_number)
		{
			cout << "test_invalid_string FAILED! test1\n";
			return false;
		}
	}

	try
	{
		result = calculate(test2);
		cout << "test_invalid_string FAILED! test2\n";
		return false;
	}
	catch (const invalid_argument err)
	{
		if (err.what() != log_error_number)
		{
			cout << "test_invalid_string FAILED! test2\n";
			return false;
		}
	}

	try
	{
		result = calculate(test3);
		cout << "test_invalid_string FAILED! test3\n";
		return false;
	}
	catch (const invalid_argument err)
	{
		if (err.what() != log_error_number)
		{
			cout << "test_invalid_string FAILED! test3\n";
			return false;
		}
	}

	try
	{
		result = calculate(test4);
		cout << "test_invalid_string FAILED! test4\n";
		return false;
	}
	catch (const invalid_argument err)
	{
		if (err.what() != log_error_number)
		{
			cout << "test_invalid_string FAILED! test4\n";
			return false;
		}
	}

	try
	{
		result = calculate(test5);
		cout << "test_invalid_string FAILED! test5\n";
		return false;
	}
	catch (const invalid_argument err)
	{
		if (err.what() != log_error_operator)
		{
			cout << "test_invalid_string FAILED! test5\n";
			return false;
		}
	}

	try
	{
		result = calculate(test6);
		cout << "test_invalid_string FAILED! test6\n";
		return false;
	}
	catch (const invalid_argument err)
	{
		if (err.what() != log_error_operator)
		{
			cout << "test_invalid_string FAILED! test6\n";
			return false;
		}
	}

	cout << "test_invalid_string COMPLETED!\n";
	return true;
}

// testing expression with substraction
bool test_with_subtraction()
{
	int result = 0;

	string test1("1--2");
	string test2("1*2--3");
	string test3("-1");
	string test4("1*-2");
	string test5("2/ -1");

	try
	{
		if (calculate(test1) != 3)
		{
			cout << "test_with_subtraction FAILED! test1\n";
			return false;
		}
		if (calculate(test2) != 5)
		{
			cout << "test_with_subtraction FAILED! test2\n";
			return false;
		}
		if (calculate(test3) != -1)
		{
			cout << "test_with_subtraction FAILED! test3\n";
			return false;
		}
		if (calculate(test4) != -2)
		{
			cout << "test_with_subtraction FAILED! test4\n";
			return false;
		}
		if (calculate(test5) != -2)
		{
			cout << "test_with_subtraction FAILED! test5\n";
			return false;
		}
	}
	catch (const invalid_argument err)
	{
		cout << "test_with_subtraction FAILED! There should be no exception\n";
		return false;
	}

	cout << "test_with_subtraction COMPLETED!\n";
	return true;
}

// testing expression with double digit
bool test_with_double_digit()
{
	int result = 0;
	string log("");

	string test1("1--12");
	string test2("1*2--31");
	try
	{
		if (calculate(test1) != 13)
		{
			cout << "test_with_double_digit FAILED! test1\n";
			return false;
		}
		if (calculate(test2) != 33)
		{
			cout << "test_with_double_digit FAILED! test2\n";
			return false;
		}
	}
	catch (const invalid_argument err)
	{
		cout << "test_with_double_digit FAILED! There should be no exception\n";
		return false;
	}

	cout << "test_with_double_digit COMPLETED!\n";
	return true;
}

// testing expression with zeros
bool test_with_zeros()
{
	int result = 0;
	string log("");

	string test1("0 + 0 -0 *0");
	string test2("1+2+ -3 / 0");
	try
	{
		if (calculate(test1)!=0)
		{
			cout << "test_with_zeros FAILED! test1\n";
			return false;
		}
	}
	catch (invalid_argument err)
	{
		cout << "test_with_zeros FAILED! There should be no exception\n";
		return false;
	}
	try
	{
		result = calculate(test2);
		cout << "test_with_zeros FAILED! test2\n";
		return false;
	}
	catch (invalid_argument err)
	{
		if (err.what() != log_error_division_by_zero)
		{
			cout << "test_with_zeros FAILED! test2\n";
			return false;
		}
	}

	cout << "test_with_zeros COMPLETED!\n";
	return true;
}

// testing the big expressions
bool test_big_expressions()
{
	int result = 0;
	string log("");

	string test1("14+-12*2-23/-2");
	string test2("42 + -40 /2/2-1");
	try
	{
		if (calculate(test1) != 1)
		{
			cout << "test_big_expressions FAILED! test1\n";
			return false;
		}
		if (calculate(test2) != 1)
		{
			cout << "test_big_expressions FAILED! test2\n";
			return false;
		}
	}
	catch (const std::exception&)
	{
		if (calculate(test1) != 1)
		{
			cout << "test_big_expressions FAILED! There should be no exception\n";
			return false;
		}
	}

	cout << "test_big_expressions COMPLETED!\n";
	return true;
}

int main()
{
	// return 1 if exist a failed test
	if (
		!test_invalid_string() ||
		!test_with_subtraction() ||
		!test_with_double_digit() ||
		!test_with_zeros() ||
		!test_big_expressions()
		)
	{
		return 1;
	}
	else // else return 0
	{
		cout << "All test completed!\n";
		return 0;
	}
}