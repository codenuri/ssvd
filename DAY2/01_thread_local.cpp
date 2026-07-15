#include <iostream>
#include <thread>
#include <string_view>

// 3의 배수를 차례대로 반환 하는 함수 만들기
// => 3, 6, 9
int next3times()
{
//	int n = 0;			// 지역변수,        stack 에 생성,          함수 호출 종료시 파괴
	static int n = 0;	// static 지역변수, static storage 에 생성, 함수 호출 종료되어도 파괴 안됨

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





