#include <iostream>
#include <thread>
#include "chronometry.h"
constexpr int sz = 10'000;

// 핵심 
// => dereferencing(*p) 는 결국 주소를 따라가서 메모리 접근하는것
// => 루프안에서는 하지 마세요
void f1(int* p)
{
	for (int i = 0; i < sz; i++)
	{
		*p += i;
	}
	std::cout << "result: " << *p << std::endl;
}
void f2(int* p)
{
	int local = *p;
	for (int i = 0; i < sz; i++)
	{
		local += i;
	}
	*p = local;
	std::cout << "result: " << local << std::endl;
}

int main()
{
	int k = 0;
	chronometry(f1, &k);
	k = 0;
	chronometry(f2, &k);
}
