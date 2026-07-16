#include <iostream>
#include <coroutine>
#include <utility>

// C++20 
// => coroutine 을 만들기 위한 규칙만 정했습니다.
// => coroutine-framework 라고 합니다. 
// => 그래서 개발자가 coroutine 을 만들려면 "4.cpp" 의 Task 같은 클래스를 직접 설계해야 합니다

// => 뛰어난 개발자가 "Task" 를 만들고, 배포후 사용법만 알면 되지 않을까요 ?

// C++23
// => coroutine 을 규칙을 지킨 std::generator<> 가 표준에 추가
// => 사용자가 코루틴 만들때 "반환 타입" 사용하게 됩니다.

// C++26 ~ 이후 
// => 다양한 코루틴 라이브러리 추가될 예정..
// => 뿐 만 아니라 다양한 오픈소스에서 좋은 라이브러리 제공


#include <generator> // C++23 

// std::generator
// => 값을 연속적으로 반환하는 코루틴을 만들때 사용하는 타입

std::generator<int> foo()
{
	// <== 컴파일러 추가 코드 ==> 

    std::cout << "foo #1\n";
    co_yield 1;			

    std::cout << "foo #2\n";
    co_yield 2;
    
    std::cout << "foo #3\n";
}  
int main()
{
    std::generator<int> gen = foo();	

	// std::generator<int> 의 재미있는 규칙
	// => resume() 을 하는 방법이 STL 반복자 스타일 입니다

	auto first = gen.begin();		// resume()	- foo #1

	std::cout << *first << '\n';	// 반환값 1

	++first;	// resume()	- foo #2
				// first.operator++() { coro.resume(); } 의 원리 입니다

	std::cout << *first << '\n';	// 반환값 2

	++first;	// resume(); - foo #2
}


// 컴파일시 -std=c++23 필요