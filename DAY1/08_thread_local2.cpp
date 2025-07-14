#include <iostream>
#include <thread>
#include <string>

// std::cout 이야기

// std::cout : 정체는 전역변수 입니다.
/*
namespace std
{
	class ostream 	
	{
	
	};
	ostream cout; // <== std 이름 공간안에 있는 전역변수
				  //     모든 스레드가 공유하고, 내부 버퍼도 공유하게 됩니다.
				  // 따라서,멀티 스레드 환경에서 사용시 출력을 깨질수 있습니다.
}
*/
// C++20 "syncstream"  화면 출력시 동기화되는 C++ 표준 스트림
#include <syncstream>

int next3times()
{
	thread_local int n = 0;

	n = n + 3;
	return n;
}

void foo(const std::string& name)
{
	std::osyncstream out(std::cout); // <== 이렇게 사용

	out << name << " : " << next3times() << std::endl; // 3
	out << name << " : " << next3times() << std::endl; // 6
	out << name << " : " << next3times() << std::endl; // 9
}

int main()
{
//	foo("A");
	
	// foo 를 2개의 스레드가 동시 실행
	std::thread t1(foo, "A");
	std::thread t2(foo, "\tB");

	t1.join();
	t2.join();
}

// 메모리와 스레드
//							소유자								파괴
// stack 				: 스레드 소유, 스레드당 한개		   함수 호출종료시 파괴
// heap  				: 프로세스 소유, 모든 스레드가 공유		free, delete 시 파괴
// data(static_storage) : 프로세스 소유, 모든 스레드 공유	    함수 호출종료되어도 파괴 안됨
// TSS(TLS)			    : 스레드 소유, 스레드당 한개			함수 호출종료되어도 파괴 안됨


// 프로세스가 생성(프로그램이 실행되면)
// 1. 전역변수 공간이 할당되고
// 2. 힙 메모리가 생성됩니다.
// 3. 주스레드가 생성됩니다.
//   => 주스레드의 stack 이 생성되고 (보통 1M, 컴파일/link 옵션에서 크기 변경가능)
//   => 주스레드의 TSS 공간이 할당 됩니다.

// 이제 새로운 스레드 생성시
// 1. 새로운 스레드를 위한 스레드가 스택이 할당 됩니다
// 2. 새로운 스레드를 위한 TSS 공간이 할당됩니다.(크기는 OS 마다 다른데, 
// 											Windows os 는 보통 sizeof(int)*1088 )
//				=> TSS 는 공간 제약이 있으므로 많은 메모리가 스레드 별로 필요하면
//				=> 힙 할당후, 주소만 TSS 에 보관하시면 됩니다.