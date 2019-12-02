enum token_type { NUMBER, STRING };

struct token
{
	std::string str;
	token_type type;
};

using write_messege = void(*)();
using calback_token = void(*)(const token& tkn);

class parser
{
	std::string str;
public:
	parser(const std::string& s);
	void set_string(const std::string& s);
	void set_f_start(void(*f)());
	void set_f_token(void(*f)(const token& tkn));
	void set_f_end(void(*f)());
	std::list<token> parse();

private:
	bool is_number(const std::string& s);
	write_messege f_start;
	calback_token f_token;
	write_messege f_end;
};