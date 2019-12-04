#include <string>
#include <list>
#include "parser.h"
#include <iostream>



parser::parser(const std::string& s)
{
	str = s;
	f_start = nullptr;
	f_token = nullptr;
	f_end = nullptr;
}

void parser::set_f_start(write_messege f)
{
	f_start = f;
}

void parser::set_f_token(calback_token f)
{
	f_token = f;
}

void parser::set_f_end(write_messege f)
{
	f_end = f;
}

void parser::set_string(const std::string& s)
{
	str = s;
}

std::list<token> parser::parse()
{
	//call f_start
	if (f_start != nullptr)
		f_start();

	std::list<token> result;
	std::string cur_str = "";
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
			cur_str.append(1,str[i]);
		else
		{
			if (!cur_str.empty())
			{
				token new_token;
				new_token.str = cur_str;
				if (is_number(new_token.str))
					new_token.type = NUMBER;
				else
					new_token.type = STRING;
				result.push_back(new_token);
				cur_str.clear();
				//call f_token
				if (f_token != nullptr)
					f_token(new_token);
			}
		}
	}
	// после выхода из цикла могла остаться необработанная строчка
	if (!cur_str.empty())
	{
		token new_token;
		new_token.str = cur_str;
		if (is_number(new_token.str))
			new_token.type = NUMBER;
		else
			new_token.type = STRING;
		result.push_back(new_token);
		cur_str.clear();
		//call f_token
		if (f_token != nullptr)
			f_token(new_token);
	}

	//call f_end
	if (f_end != nullptr)
		f_end();

	return result;
}

bool parser::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
