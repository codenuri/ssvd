// 14_false_sharing1.cpp
#include "chronometry.h"
#include <thread>  
#include <iostream>

const int sz = 10'000'000; 

// 해결책 : n1, n2 가 하나의 캐쉬에 같이 놓이지 않도록 "떨어뜨려야" 합니다.

// 방법 #1. 중간에 padding 변수를 넣으세요

/*
long long n1 = 0;
char padding[64]; // 64 byte
long long n2 = 0;
*/

// 방법 #2. 변수의 시작 주소를 64 byte 단위로 만드는 문법 사용
// => C++11 부터 지원

alignas(64) long long n1 = 0;
alignas(64) long long n2 = 0;


void f1()
{
	for (int i = 0; i < sz; i++)
	{
		n1 += 1;
	}
}

void f2()
{
	for (int i = 0; i < sz; i++)
	{
		n2 += 1;
	}
}

void single_thread()
{
	f1();
	f2();
}


void multi__thread()
{	
	std::thread t1(f1);
	std::thread t2(f2);
	t1.join();
	t2.join();
}

int main()
{
	// 아래 코드 실행시, 순서도 바꿔가면서 확인해 보세요
//	chronometry(single_thread);
	chronometry(multi__thread);
	chronometry(single_thread);

	// 아래 주소가 핵심 입니다
	// => 2개의 변수가 연속적으로 되어 있는지 확인 하세요
	printf("%p\n", &n1);
	printf("%p\n", &n2);
}
