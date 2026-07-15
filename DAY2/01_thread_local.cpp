#include <iostream>
#include <thread>
#include <string_view>
// 메모리의 종류와 소유자

// stack          : 지역변수 			   , 함수 호출 종료시 파괴,     스레드당 한개
// static storage : 전역변수/static 지역변수, 함수 호출 종료시 파괴안됨. 프로세스 소유(모든스레드공유)
// thread local storage : 					함수 호출 종료시 파괴안됨. 스레드당 한개
//											(스레드당 한개의 static storage 공간)		
//   => 전역변수와 static 지역변수 만들때 사용		

thread_local int g1 = 0;  // 스레드당 한개의 전역변수
int g2 = 0;				  // 모든 스레드가 공유하는 전역변수(프로세스당 한개)

// 3의 배수를 차례대로 반환 하는 함수 만들기
// => 3, 6, 9
int next3times()
{
//	int n = 0;			// 지역변수,        stack 에 생성,          함수 호출 종료시 파괴
//	static int n = 0;	// static 지역변수, static storage 에 생성, 함수 호출 종료되어도 파괴 안됨
						// => 프로세스당 한개, 모든 스레드가 공유

	thread_local int n = 0;	// 스레드당 한개의 static 지역변수로 생각하시면 됩니다.

	n = n + 3;
	return n;
}
void foo(std::string_view name)
{
	std::cout << name << " : " << next3times() << std::endl; // 3
	std::cout << name << " : " << next3times() << std::endl; // 6
	std::cout << name << " : " << next3times() << std::endl; // 9
}
int main()
{
//	foo("A");
	std::jthread t1(foo, "A");
	std::jthread t2(foo, "\tB");	
}





