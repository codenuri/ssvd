// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main()
{
	// 람다 표현식의 활용
	// 1. std::find_if() 등을 사용시 인자로 전달 
	//    std::find_if( first, last, [](int n) { return n % 3 == 0;});

	// 2. auto 변수에 담아서 일반 함수 처럼 사용 
	[](int a, int b) { return a + b; };
}
