enum token_type { NUMBER, STRING };

struct token
{
	std::string str;
	token_type type;
};

std::list<token> parse(const std::string& str,	//
	void(*)(const token& tkn) = nullptr,		//
	void(*f_start)() = nullptr, void(*f_end)() = nullptr);