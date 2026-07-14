#include "chronometry.h" // <= 수업용으로 만든 헤더. 
#include <thread>

// 00_thread.cpp

// 오랜 시간이 걸리는 2개의 작업
//-------------------------------------
void do_long_work1()
{
	int s = 0;
	for(int i = 0; i < 100'000'000; i++) { s += i; }
}
void do_long_work2()
{
	int s = 0;
	for(int i = 0; i < 100'000'000; i++) { s += i; }
}
//-------------------------------------
void single_thread()
{
	// 하나의 스레드로 2개의 작업을 차례대로 실행
	do_long_work1();
	do_long_work2();
}
void multi_thread()
{
	// 2개의 작업을 별도의 스레드로 각각 실행
	std::jthread t1(do_long_work1);
	std::jthread t2(do_long_work2);
}
int main()
{
	chronometry(single_thread);
	chronometry(multi_thread);

	// chronometry : 1번째 인자로 전달된 함수를 실행하고, 소요시간을 출력
	// usage       : chronometry(function, arg1, arg2 ...)
	//				 function(arg1, arg2, ... )
}