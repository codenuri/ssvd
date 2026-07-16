// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>

// 람다 표현식을 정확히 이해하려면
// 1. 함수 객체를 먼저 알아야 합니다
// 2. 람다표현식은 함수 객체를 자동으로 만드는 표기법

// 핵심 : 함수 객체란 ?
// => () 연산자를 재정의 해서 함수 처럼 사용가능한 클래스

// 왜 일반함수를 사용하면 되는데 함수 객체를 사용하나요 ?
// => 함수 보다 좋은점이 많습니다
// 1. 상태를 가지는 함수
// 2. 일반함수 보다 빠른 경우가 있다
// 3. ....
// 외에 수많은 장점

struct Plus
{
	int operator()(int a, int b) 
	{
		return a + b;
	}
};

int main()
{
	Plus p;	// Plus 는 구조체 이므로 p 는 객체 입니다. 함수가 아닌 객체

	int n1 = p(1,2); 			// 객체인 p를 함수 처럼 사용합니다. 함수 객체 라고 합니다.
	int n2 = p.operator()(1,2); // 원리. 이렇게 직접 표기해도 됩니다.

	// ++p; // p.operator++()
	// p(); // p.operator()()
	// p(1,2); // p.operator()(1,2)

	int n3 = std::max(1, 2); // C++98 버전의 C++ 표준 함수. 일반 함수 입니다.
	int n4 = std::range::max(1, 2); // C++20 은 거의 모든 표준함수를 새로 만들었습니다. 함수객체입니다.
	int n5 = std::range::max.operator()(1, 2); // 이렇게 사용가능
}