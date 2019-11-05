#include <iostream>
using namespace std;
#include <string>
#include <exception>
#include "calculator.h"

int main(int argc, char *argv[])
{
	if (argc != 2) // check if expression is passed
	{
		printf("Error! Need two arguments: calc.exe \"expression\"\n");
		return 1;
	}

	string expression(argv[1]);
	string log(""); // contains error message after calculation (need for testing)
	int result;

	try
	{
		result = calculate(expression);
		cout << result;
		return 0;
	}
	catch (invalid_argument err)
	{
		cout << err.what();
		return 1;
	}
}