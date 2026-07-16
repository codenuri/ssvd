#include <iostream>
#include <coroutine>
#include <utility>
#include <generator> 
#include <vector>

int main()
{
	std::vector<int> v = {1, 2, 3, 4, 5};

	for( auto e : v )
	{
		std::cout << e << '\n';
	}
	//-------------------------------------------------
	// 위 for 문의 원리를 생각해 봅시다.
	// 위 코드를 컴파일러가 아래 처럼 변경합니다
	auto&& cont = v;
	auto first = cont.begin();  // v가 배열이면 "auto first = std::begin(cont)"
	auto last  = cont.end();

	for( ; first != last; ++first ) // legacy for 
	{	
		auto e = *first;
		//-------------------------
		std::cout << e << '\n';
	}
	//-------------------------------------------------	
}


