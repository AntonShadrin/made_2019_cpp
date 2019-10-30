#include <iostream>
using namespace std;
#include <string>
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

	if (calculate(expression, result, log)) // print result if calculation completed
	{
		cout << result << "\n";
		return 0;
	}
	else // print error if calculation failed
		cout << log;
	return 1;
}