enum token_type { NUMBER, STRING };

struct token
{
	std::string str;
	token_type type;
};

using write_messege = void(*)();
using calback_token_number = void(*)(const int& tkn);
using calback_token_string = void(*)(const std::string& tkn);

class parser
{
	std::string str;
public:
	parser(const std::string& s);
	void set_string(const std::string& s);
	void set_f_start(write_messege f);
	void set_f_token_number(calback_token_number f);
	void set_f_token_string(calback_token_string f);
	void set_f_end(write_messege f);
	std::list<token> parse();

private:
	bool is_number(const std::string& s);
	write_messege f_start;
	calback_token_number f_token_number;
	calback_token_string f_token_string;
	write_messege f_end;
};