#include "BigInt.h"

bool test()
{
	BigInt a = 1234567890;
	BigInt b(9876543210);
	BigInt c = a;
	BigInt d(b);
	BigInt e = c + d;
	if (a > b)
		return false;
	if (b <= a + c)
		return false;
	if (a != c)
		return false;
	if ((a + b + 1234 - c - d) != 1234)
		return false;
	if (!(a + -c + b == d))
		return false;
	if (!(a + b == e))
		return false;
	return true;
}

int main()
{
	if (test())
	{
		std::cout << "TEST COMPLETED!\n";
		return 0;
	}
	std::cout << "FAILED TEST!\n";
	return 1;
}