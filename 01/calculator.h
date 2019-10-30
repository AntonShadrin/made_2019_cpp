#ifndef CALCULATOR_H
#define CALCULATOR_H
using std::string;

void SkipSpaces(string &str);

// first priority operation
bool get_number(string &str, int &result);

// second priority operation
int try_MulDiv(string &str);

// third priority operation
int try_AddSub(std::string &str);

// caolculate expression in str. log contains error message after calculation (need for testing)
bool calculate(string &str, int &result, string &log);

#endif
