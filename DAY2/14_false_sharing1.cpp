// 14_false_sharing1.cpp
#include "chronometry.h"
#include <thread>  
#include <iostream>

const int sz = 10'000'000; 

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
	// chronometry(함수이름) : 함수가 실행되는 데 걸리는 시간 측정. chronometry.h 에 소스 있습니다
	// 아래 결과는 "싱글스레드 버전"이 훨씬 빠릅니다.( 환경에 따라 다를수 있습니다. )
	
	// => 왜 이럴까요 ?
	// => 캐쉬의 가짜 공유 현상(false sharing) 문제 입니다.
	// => 해결은 다음 소스

	// 아래 코드 실행시, 순서도 바꿔가면서 확인해 보세요
//	chronometry(single_thread);
	chronometry(multi__thread);
	chronometry(single_thread);
}
