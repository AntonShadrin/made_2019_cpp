#include <cstdint>
#include <sstream>
#include <iostream>
#include <string>
#include <assert.h>

enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer
{
	static const char Separator = ' ';
	std::ostream& out_;
public:
	explicit Serializer(std::ostream& out)
		: out_(out)
	{
	}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}

private:
	// process использует variadic templates
	template <class T>
	Error process(T&& val)
	{
		if (load(val) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		if (!out_)
			return Error::CorruptedArchive;
		return Error::NoError;
	}

	template <class T, class... ArgsT>
	Error process(T&& val, ArgsT&&... args)
	{
		if (load(val) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		out_ << Separator;
		if (out_.bad())
			return Error::CorruptedArchive;
		return process(std::forward<ArgsT>(args)...);
	}


	template <class T>
	Error load(T& value)
	{
		return Error::CorruptedArchive;
	}
	template <>
	Error load<bool>(bool& value)
	{
		if (value)
			out_ << "true";
		else
			out_ << "false";
		if (out_.bad())
			return Error::CorruptedArchive;
		return Error::NoError;
	}
	template <>
	Error load<uint64_t>(uint64_t& value)
	{
		out_ << value;
		if (out_.bad())
			return Error::CorruptedArchive;
		return Error::NoError;
	}

};

class Deserializer
{
	std::istream& in_;
public:
	explicit Deserializer(std::istream& in)
		: in_(in)
	{
	}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}

private:
	// process использует variadic templates
	template <class T>
	Error process(T&& val)
	{
		if (load(val) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		return Error::NoError;
	}
	template <class T, class... ArgsT>
	Error process(T&& val, ArgsT&&... args)
	{
		if (load(val) == Error::CorruptedArchive)
			return Error::CorruptedArchive;
		return process(std::forward<ArgsT>(args)...);
	}

	template <class T>
	Error load(T& value)
	{
		return Error::CorruptedArchive;
	}
	template <>
	Error load<bool>(bool& value)
	{
		if (!in_)
			return Error::CorruptedArchive;
		std::string text;
		in_ >> text;

		if (text == "true")
			value = true;
		else if (text == "false")
			value = false;
		else
			return Error::CorruptedArchive;

		return Error::NoError;
	}
	template <>
	Error load<uint64_t>(uint64_t& value)
	{
		if (!in_)
			return Error::CorruptedArchive;
		in_ >> value;
		return Error::NoError;
	}
};

struct Data
{
	uint64_t a;
	bool b;
	uint64_t c;
	bool d;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

bool test_serializator()
{
	Data x{ 10, true, 20 };
	std::stringstream stream;

	Serializer serializer(stream);

	const Error err_Sx = serializer.save(x);
	if (err_Sx != Error::NoError) return false;

	Data y{ 5, false, 6 };

	Deserializer deserializer(stream);
	const Error err_DSy = deserializer.save(y);
	//устанавливаем позицию ввода вывода в 0, иначе шайтанство какое-то!
	stream.seekp(0);
	stream.seekg(0);


	if (err_DSy != Error::NoError) return false;
	if (!((x.a == y.a) && (x.b == y.b) && (x.c == y.c))) return false;

	Data z{ 100, true, 200 };
	const Error err_Sy = serializer.save(y);
	if (err_Sy != Error::NoError) return false;

	const Error err_DSz = deserializer.save(z);
	if (err_DSz != Error::NoError) return false;
	if (!((z.a == y.a) && (z.b == y.b) && (z.c == y.c))) return false;
	stream.str("");
	return true;
}

int main()
{
	if (!test_serializator())
	{
		std::cout << "test_serializator FAILED!!";
		return 1;
	}

	std::cout << "test_serializator COMPLETED!!";
	return 1;
}