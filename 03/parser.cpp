#include <string>
#include <list>
#include "parser.h"
#include <iostream>



parser::parser(const std::string& s)
{
	str = s;
	f_start = nullptr;
	f_token_number = nullptr;
	f_token_string = nullptr;
	f_end = nullptr;
}

void parser::set_f_start(write_messege f)
{
	f_start = f;
}

void parser::set_f_token_number(calback_token_number f)
{
	f_token_number = f;
}

void parser::set_f_token_string(calback_token_string f)
{
	f_token_string = f;
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
				{
					new_token.type = NUMBER;
					//call f_token_number
					if (f_token_number != nullptr)
					{
						int num_tkn = atoi(new_token.str.c_str());
						f_token_number(num_tkn);
					}
				}
				else
				{
					new_token.type = STRING;
					//call f_token_string
					if (f_token_string != nullptr)
						f_token_string(new_token.str);
				}
				result.push_back(new_token);
				cur_str.clear();
			}
		}
	}
	// после выхода из цикла могла остаться необработанная строчка
	if (!cur_str.empty())
	{
		token new_token;
		new_token.str = cur_str;
		if (is_number(new_token.str))
		{
			new_token.type = NUMBER;
			//call f_token_number
			if (f_token_number != nullptr)
			{
				int num_tkn = atoi(new_token.str.c_str());
				f_token_number(num_tkn);
			}
		}
		else
		{
			new_token.type = STRING;
			//call f_token_string
			if (f_token_string != nullptr)
				f_token_string(new_token.str);
		}
		result.push_back(new_token);
		cur_str.clear();
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
