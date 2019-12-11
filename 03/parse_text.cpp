#include <iostream>
#include <string>
#include <list>
#include "parser.h"

// пишет числовой токен
void token_number_func(const token& tkn)
{
	std::cout << tkn.str << " it's NUMBER token\n";
}

// пишет строковый токен
void token_string_func(const token& tkn)
{
	std::cout << tkn.str << " it's STRING token\n";
}

// объявляет начало разбора строки
void start_func()
{
	std::cout << "START!\n";
}

// объявляет конец разбора строки
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

	// вызов с функциями
	parser str_parser(line);
	str_parser.set_f_start(start_func);
	str_parser.set_f_token_number(token_number_func);
	str_parser.set_f_token_string(token_string_func);
	str_parser.set_f_end(end_func);
	std::list<token> result = str_parser.parse();
	return 0;
}