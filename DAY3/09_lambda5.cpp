// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

bool foo(int n) { return n % 3 == 0; }	 // main 지역변수 k 사용하기 어렵다

struct IsModulus 
{
	int value;							// main 지역변수 k 를 여기에 보관
	IsModulus(int v) : value(v) {}
	bool operator()(int n) { return n % value  == 0; }
};

int main()
{
	std::vector<int> v = {1,2,3,4,5,6};

	int k = 3;

	// std::find_if( first, last, 단항 함수 ) 에서 단항 함수는
	// => 일반함수, 함수객체, 람다표현식 모두 가능합니다

	// [람다 표현식 사용시 장점]
	// => 지역변수 k 를 아주 쉽게 캡쳐 할수 있다
	// => 일반함수 : 어렵다
	// => 함수객체 : 가능하지만 클래스를 직접 만들어야 한다.

	auto p1 = std::find_if(v.begin(), v.end(), [] (int n) { return n % 3 == 0; } ); 
	auto p1 = std::find_if(v.begin(), v.end(), [k](int n) { return n % k == 0; } ); 

}
