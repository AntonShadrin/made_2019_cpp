#include <cstdint>
#include <sstream>
#include <string>

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