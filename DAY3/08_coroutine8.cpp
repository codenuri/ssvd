#include <iostream>
#include <coroutine>
#include <utility>
#include <generator> 

// C++ coroutine 으로 파이썬 range 만들기
std::generator<int> range(int start, int end)
{
	for( int i = start; i < end; ++i ) 
		co_yield i;
}

int main()
{	
	// 파이썬 코드 - 0 ~ 9 를 순회할때 사용
	// range : start, end 값을 연속적으로 생성
	// for e in range(0, 10)

	for( auto e : range(0, 10) )
	{
		std::cout << e << '\n';
	}
		
}
