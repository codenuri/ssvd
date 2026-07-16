//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 100000000;

// 해결책 #3. 전역변수를 직접 사용하지 말고(공유자원을 직접 사용하는 것은 항상 좋지 않다)
// 1. 지역변수 에 전역변수값을 옮겨 담고
// 2. 지역변수로 연산후
// 3. 지역변수의 값을 다시 전역으로 이동
unsigned long long n1 = 0;
unsigned long long n2 = 0;

void f1()
{
	int local = n1;
	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}
	n1 = local;
	std::cout << "f1 result: " << n1 << std::endl;
}
void f2()
{
	int local = n2;
	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}
	n2 = local;
	std::cout << "f2 result: " << n2 << std::endl;
}

void single_thread()
{
	n1 = 0;
	n2 = 0;
	f1();
	f2();
}

void multi_thread()
{
	n1 = 0;
	n2 = 0;

	std::jthread t1(f1);
	std::jthread t2(f2);
}

int main()
{
	std::cout << "&n1 : " << &n1 << '\n';
	std::cout << "&n2 : " << &n2 << '\n';

	chronometry(single_thread);
	chronometry(multi_thread);
}
