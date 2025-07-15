// 14_false_sharing1.cpp
#include "chronometry.h"
#include <thread>  
#include <iostream>

const int sz = 10'000'000; 

// false sharing(가짜 공유) 에 대한 또 다른 해결책
// => 전역변수(공유자원)을 직접 사용하지 말고
// => 지역변수에 담아서 연산한후
// => 결과만 전역변수에 옮긴다

long long n1 = 0;
long long n2 = 0;

void f1()
{
	// 공유자원의 값을 지역변수로
	int local = n1;

	// 이제 모든 연산은 지역변수로
	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}
	
	// 최종결과만 공유자원으로
	n1 = local;
}


void f2()
{
	int local = n2;

	for (int i = 0; i < sz; i++)
	{
		local += 1;
	}

	n2 = local;
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
