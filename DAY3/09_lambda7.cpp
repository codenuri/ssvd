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
	// => 람다 표현식을 보면 
	//    "컴파일러가 클래스를 만들었고"
	//    "해당 타입의 객체를 생성한 코드" 로 생각하세요

	auto add = [](int a, int b) { return a + b; };
			   // class xxxx{}; xxxx();
			   // 결국 add 는 컴파일러가 만든 클래스(함수객체)타입의 객체

	int n1 = add(1, 2); // a + b;
	int n2 = add.operator()(1, 2); // 함수 객체이므로 이렇게도 사용가능

	// 특징
	// 1. 위 코드는 함수 안에서 함수를 만든것, main 함수에서 add 함수 만들기
	//    => C++ 기본 문법에서는 함수안에서 함수 만들수 없습니다
	// 2. add 같은 함수객체는 다른 함수에 인자로 전달되면 일반함수보다 빠르게 동작
}
