#include <iostream>     // 동기화 출력 기능 없음
#include <syncstream>   // 동기화 stream, C++20 부터 지원
#include <thread>
#include <string_view>

int next3times()
{
	thread_local int n = 0;	

	n = n + 3;
	return n;
}
void foo(std::string_view name)
{
	std::osyncstream out(std::cout); // 동기화를 해서 std::cout 으로 출력
									 // out 이 데이타를 동기화해서 버퍼에 모으고
									 // std::cout 으로 출력

	// 아래 코드는 줄단위 동기화 아닙니다.
	// => 모든 데이타를 일단 out 내부 버퍼에 모으고
	// => out 의 소멸자에서 한번에 std::cout 으로 출력
//	out << name << " : " << next3times() << std::endl; // 3
//	out << name << " : " << next3times() << std::endl; // 6
//	out << name << " : " << next3times() << std::endl; // 9

	// 줄단위 동기화 출력이 필요하면 아래 처럼..
	// std::flush_emit : 현재까지 버퍼에 모은 데이터를 출력
	out << name << " : " << next3times() << '\n' << std::flush_emit;
	out << name << " : " << next3times() << '\n' << std::flush_emit;
	out << name << " : " << next3times() << '\n' << std::flush_emit;
}
int main()
{
	std::jthread t1(foo, "A");
	std::jthread t2(foo, "\tB");	
}





