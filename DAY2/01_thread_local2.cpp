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

	out << name << " : " << next3times() << std::endl; // 3
	out << name << " : " << next3times() << std::endl; // 6
	out << name << " : " << next3times() << std::endl; // 9
}
int main()
{
	std::jthread t1(foo, "A");
	std::jthread t2(foo, "\tB");	
}





