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
	string log("");
	string test1(" 1 + 1 -/ 2");
	string test2("--1");
	string test3("");
	string test4("abc");
	string test5("1 % 2");
	string test6("1 +2 plus 3");
	if (calculate(test1, result, log) || log != log_error_number)
	{ cout << "test_invalid_string FAILED! test1\n"; return false; }
	if (calculate(test2, result, log) || log != log_error_number)
	{ cout << "test_invalid_string FAILED! test2\n"; return false; }
	if (calculate(test3, result, log) || log != log_error_number)
	{ cout << "test_invalid_string FAILED! test3\n"; return false; }
	if (calculate(test4, result, log) || log != log_error_number)
	{ cout << "test_invalid_string FAILED! test4\n"; return false; }
	if (calculate(test5, result, log) || log != log_error_operator)
	{ cout << "test_invalid_string FAILED! test5\n"; return false; }
	if (calculate(test6, result, log) || log != log_error_operator)
	{ cout << "test_invalid_string FAILED! test6\n"; return false; }

	cout << "test_invalid_string COMPLETED!\n";
	return true;
}

// testing expression with substraction
bool test_with_subtraction()
{
	int result = 0;
	string log("");

	string test1("1--2");
	string test2("1*2--3");
	string test3("-1");
	string test4("1*-2");
	string test5("2/ -1");
	if (!calculate(test1, result, log) || result!= 3 || log != log_success)
	{ cout << "test_with_subtraction FAILED! test1\n"; return false; }
	if (!calculate(test2, result, log) || result!= 5 || log != log_success)
	{ cout << "test_with_subtraction FAILED! test2\n"; return false; }
	if (!calculate(test3, result, log) || result!= -1 || log != log_success)
	{ cout << "test_with_subtraction FAILED! test3\n"; return false; }
	if (!calculate(test4, result, log) || result!= -2 || log != log_success)
	{ cout << "test_with_subtraction FAILED! test4\n"; return false; }
	if (!calculate(test5, result, log) || result!= -2 || log != log_success)
	{ cout << "test_with_subtraction FAILED! test5\n"; return false; }

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
	if (!calculate(test1, result, log) || result != 13 || log != log_success)
	{
		cout << "test_with_double_digit FAILED! test1\n"; return false;
	}
	if (!calculate(test2, result, log) || result != 33 || log != log_success)
	{
		cout << "test_with_double_digit FAILED! test2\n"; return false;
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
	if (!calculate(test1, result, log) || result!=0 || log != log_success)
	{
		cout << "test_with_zeros FAILED! test1\n"; return false;
	}
	if (calculate(test2, result, log) || log != log_error_division_by_zero)
	{
		cout << "test_with_zeros FAILED! test1\n"; return false;
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
	if (!calculate(test1, result, log) || result != 1 || log != log_success)
	{
		cout << "test_big_expressions FAILED! test1\n"; return false;
	}
	if (!calculate(test2, result, log) || result != 1 || log != log_success)
	{
		cout << "test_big_expressions FAILED! test2\n"; return false;
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