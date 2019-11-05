#include <iostream>
#include "allocator.h"

bool test_alloc()
{
	LinearAllocator myAlloc(1000);
	char* buf_1_600 = myAlloc.alloc(600);
	if (buf_1_600 == nullptr)
	{
		std::cout << "test_alloc FALLED! test1 error!\n";
		return false;
	}
	char* buf_2_300 = myAlloc.alloc(300);
	if (buf_2_300 != buf_1_600 +600)
	{
		std::cout << "test_alloc FALLED! test2 error!\n";
		return false;
	}
	char* buf_3_200 = myAlloc.alloc(200);
	if (buf_3_200 != nullptr)
	{
		std::cout << "test_alloc FALLED! test3 error!\n";
		return false;
	}
	char* buf_4_100 = myAlloc.alloc(100);
	if (buf_4_100 != buf_2_300 + 300)
	{
		std::cout << "test_alloc FALLED! test4 error!\n";
		return false;
	}
	myAlloc.reset();
	char* buf_5_1001 = myAlloc.alloc(1001);
	if (buf_5_1001 != nullptr)
	{
		std::cout << "test_alloc FALLED! test5 error!\n";
		return false;
	}
	char* buf_6_1000 = myAlloc.alloc(1000);
	if (buf_6_1000 != buf_1_600)
	{
		std::cout << "test_alloc FALLED! test6 error!\n";
		return false;
	}
	return true;
}

int main()
{
	if (test_alloc())
	{
		std::cout << "All test completed!\n";
		return 0;
	}
	else
	{
		return 1;
	}
}