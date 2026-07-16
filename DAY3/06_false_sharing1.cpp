//00_false_sharing1
#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 100000000;

unsigned long long n1 = 0;
unsigned long long n2 = 0;

// f1() 함수는 전역변수 n1 만 사용
// f2() 함수는 전역변수 n2 만 사용

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
	// 한개의 스레드로 f1(), f2() 순차 실행
	f1();
	f2();
}

void multi_thread()
{
	n1 = 0;
	n2 = 0;
	// f1(), f2() 를 다른 스레드로 실행
	// => 각 함수가 자신만의 전역변수 사용하므로 동기화 필요없음. 
	std::jthread t1(f1);
	std::jthread t2(f2);
}

int main()
{
	chronometry(single_thread);
	chronometry(multi_thread);
}

// 위 예제는 멀티 스레드가 빠를것 같지만..
// => 싱글 스레드 버전이 훨씬 빠릅니다.
// => 왜 그럴까요 ?
// => 해결책은 뭘까요 ?
// => 다음 단계에서 해결