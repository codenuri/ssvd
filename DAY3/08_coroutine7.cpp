#include <iostream>
#include <coroutine>
#include <utility>
#include <generator> 

std::generator<int> foo()
{
//  std::cout << "foo #1\n";
    co_yield 1;			
//  std::cout << "foo #2\n";
    co_yield 2;    
//  std::cout << "foo #3\n";
}  
int main()
{	
	// std::generator<> 로 만든 코루틴을 사용하는 일반 적인 코딩 관례
	// => range-for 의 컨테이너 위치에서 코루틴을 호출하세요

	// "6.cpp" 코드를 참고해서 아래 코드의 원리를 잘생각해 보세요

	for( auto e : foo() )
	{
		std::cout << e << '\n';
	}
	//-----------------------------------
	// 위 코드의 원리
	auto&& cont = foo();		// 컴파일러 추가 코드 실행
	auto first = cont.begin();  // 사용자 코드 호출 - 1 반환
	auto last  = cont.end();

	for( ; first != last; ++first ) 
	{	
		auto e = *first;	// 1얻기
		//-------------------------
		std::cout << e << '\n';
	}	

}
