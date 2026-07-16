//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 100000000;


// "1.cpp" 가 싱글 스레드 버전이 더 빠른 경우가 있는 이유
// => CPU 의 캐쉬 때문에...


// 해결책 #1. n1, n2 사이에 캐쉬 크기의 임의 변수를 생성해서
//           n1, n2 의 메모리를 캐쉬 크기 이상으로 떨어 뜨려 놓기


unsigned long long n1 = 0;

char padding[64]; // 64byte

unsigned long long n2 = 0;


void f1()
{
	for (int i = 0; i < sz; i++)
	{
		n1 += 1;
	}
	std::cout << "f1 result: " << n1 << std::endl;
}
void f2()
{
	for (int i = 0; i < sz; i++)
	{
		n2 += 1;
	}
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
