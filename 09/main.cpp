#include <iostream>
#include "TreadPool.h"

struct A
{
	A(int x_, int y_) : x(x_), y(y_) {}
	int x;
	int y;
};

int foo(const A& a)
{
	int z = a.x + a.y;
	return z;
}

bool test()
{
	ThreadPool pool(8);
	for (int i = 0; i < 9; ++i)
	{
		if (i % 2 == 0)
		{
			auto res = pool.exec(foo, A(1, 2));
			if (res.get() != 3)
				return false;
			std::cout << "this is " << i << " func" << std::endl;
		}
		if (i % 2 == 1)
		{
			auto res = pool.exec([]() { return 1; });
			if (res.get() != 1)
				return false;
			std::cout << "this is " << i << " func" << std::endl;
		}
	}
	return true;
}

int main()
{
	if (!test())
	{
		std::cout << "Test failed!" << std::endl;
		return 1;
	}
	std::cout << "All test completed!" << std::endl;
	return 0;
}