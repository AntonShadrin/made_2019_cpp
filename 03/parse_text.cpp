#include <iostream>
#include <string>
#include <list>
#include "parser.h"

// ����� ����� � ������ ���� �� �������������
void token_func(const token& tkn)
{
	std::cout << tkn.str;
	if (tkn.type == NUMBER)
		std::cout << " it's NUMBER token\n";
	if (tkn.type == STRING)
		std::cout << " it's STRING token\n";
}

// ��������� ������ ������� ������
void start_func()
{
	std::cout << "START!\n";
}

// ��������� ����� ������� ������
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

	// ����� � ���������
	parser str_parser(line);
	str_parser.set_f_start(start_func);
	str_parser.set_f_token(token_func);
	str_parser.set_f_end(end_func);
	std::list<token> result = str_parser.parse();
	return 0;
}