#include <iostream>
#include <string>
#include <list>
#include "parser.h"

// пишет числовой токен
void token_number_func(const int& tkn)
{
	std::cout << tkn << " it's NUMBER token\n";
}

// пишет строковый токен
void token_string_func(const std::string& tkn)
{
	std::cout << tkn << " it's STRING token\n";
}

void start_func()
{
	std::cout << "START!\n";
}

void end_func()
{
	std::cout << "END!\n";
}

bool tets_good_parse()
{
	std::string test1 = "test + 123 = test123";
	std::string test2 = "";
	// test1

	parser str_parser(test1);
	std::list<token> parse1 = str_parser.parse();
	std::list<token> result1 = { { "test",STRING }, { "+",STRING }, //
								{"123",NUMBER}, { "=",STRING }, { "test123",STRING } };
	if (parse1.size() != result1.size())
	{
		std::cout << "tets_good_parse FAILED! Error test1!\n";
		return false;
	}
	auto it_res = result1.begin();
	for (const token& tkn : result1)
	{
		if( (tkn.str != it_res->str) || (tkn.type != it_res->type) )
		{
			std::cout << "tets_good_parse FAILED! Error test1!\n";
			return false;
		}
		it_res++;
	}
	// test2
	str_parser.set_string(test2);
	std::list<token> parse2 = str_parser.parse();
	if (!parse2.empty())
	{
		std::cout << "tets_good_parse FAILED! Error test2!\n";
		return false;
	}
	return true;
}

int main()
{
	if (!tets_good_parse())
	{
		return 1;
	}
	std::cout << "All test without function COMPLETED!\n\n";

	std::cout << "Test parsing with my function\n";

	std::string test_my_func = "test + 123 = test123";
	std::cout << "input string: " << test_my_func << "\n\n";

	parser str_parser(test_my_func);
	str_parser.set_f_start(start_func);
	str_parser.set_f_token_number(token_number_func);
	str_parser.set_f_token_string(token_string_func);
	str_parser.set_f_end(end_func);
	std::list<token> result = str_parser.parse();
	return 0;
}