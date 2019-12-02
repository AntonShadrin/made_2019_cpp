#include <cstdint>
#include <sstream>
#include <iostream>
#include <string>
#include <assert.h>
#include "serialazer.h"

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