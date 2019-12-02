#include <iostream>
#include <string>
#include <list>
#include "parser.h"

// пишет токен и какому типу он соответствует
void token_func(const token& tkn)
{
	std::cout << tkn.str;
	if (tkn.type == NUMBER)
		std::cout << " it's NUMBER token\n";
	if (tkn.type == STRING)
		std::cout << " it's STRING token\n";
}

// объ€вл€ет начало разбора строки
void start_func()
{
	std::cout << "START!\n";
}

// объ€вл€ет конец разбора строки
void end_func()
{
	std::cout << "END!\n";
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Error! Need two arguments: parser_text.exe \"expression\"\n");
		return 1;
	}
	std::string line(argv[1]);

	// вызов с функци€ми
	parser str_parser(line);
	str_parser.set_f_start(start_func);
	str_parser.set_f_token(token_func);
	str_parser.set_f_end(end_func);
	std::list<token> result = str_parser.parse();
	return 0;
}