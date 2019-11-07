#include <string>
#include <list>
#include <regex>
#include "parser.h"
#include <iostream>


bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

std::list<token> parse(const std::string& str, //
	void(*f_token)(const token& tkn), //
	void (*f_start)(), void (*f_end)())
{
	//call f_start
	if (f_start != nullptr)
		f_start();

	std::list<token> result;
	std::regex regEx("[^\\s]+");
	auto begin = std::sregex_iterator(str.cbegin(), str.cend(), regEx);
	auto end = std::sregex_iterator();
	for (std::sregex_iterator i = begin; i != end; ++i)
	{
		std::smatch match = *i;
		token new_token;
		new_token.str = match.str();
		if(is_number(new_token.str))
			new_token.type = NUMBER;
		else
			new_token.type = STRING;
		result.push_back(new_token);

		//call f_token
		if (f_token != nullptr)
			f_token(new_token);
	}

	//call f_end
	if (f_end != nullptr)
		f_end();

	return result;
}