#include <iostream>
#include <string>
#include <list>
#include <regex>
#include "parser.h"

void token_func(const token& tkn)
{
	std::cout << tkn.str;
	if (tkn.type == NUMBER)
		std::cout << " it's NUMBER token\n";
	if (tkn.type == STRING)
		std::cout << " it's STRING token\n";
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
	std::list<token> parse1 = parse(test1);
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
	std::list<token> parse2 = parse(test2);
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
	std::list<token> result = parse(test_my_func, token_func, start_func, end_func);
	return 0;
}