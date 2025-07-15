// 14_false_sharing1.cpp
#include "chronometry.h"
#include <thread>  
#include <iostream>

const int sz = 1'000'0000; 

long long n1 = 0;
long long n2 = 0;

// f1은 "n1" 변수만 사용합니다.
void f1()
{
	for (int i = 0; i < sz; i++)
	{
		n1 += 1;
	}
}

// f2은 "n2" 변수만 사용합니다.
void f2()
{
	for (int i = 0; i < sz; i++)
	{
		n2 += 1;
	}
}

void single_thread()
{
	// 한개의 스레드가 2개의 작업을 순차적으로 수행
	f1();
	f2();
}


void multi__thread()
{
	// 2개의 스레드가 각각 작업을 수행.. 
	// => 공유자원등이 없으므로 동기화등도 필요 없습니다. 
	std::thread t1(f1);
	std::thread t2(f2);
	t1.join();
	t2.join();
}

int main()
{
	chronometry(single_thread);
//	chronometry(multi__thread);
}
