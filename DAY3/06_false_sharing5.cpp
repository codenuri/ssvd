#include <iostream>
#include <thread>
#include "chronometry.h"
constexpr int sz = 10'000;

void f1(int* p)
{
	for (int i = 0; i < sz; i++)
	{
		*p += i;
	}
	std::cout << "result: " << *p << std::endl;
}


int main()
{
	chronometry(f1);
//	chronometry(f2);
}
