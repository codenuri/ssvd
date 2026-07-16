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

	auto p1 = std::find_if(v.begin(), v.end(), [] (int n) { return n % 3 == 0; } ); 
	auto p2 = std::find_if(v.begin(), v.end(), [k](int n) { return n % k == 0; } ); 

	// 컴파일러의 원리
	// 람다 표현식을 보고, 함수 객체를 만드는 것
	class CompilerGeneratedName1
	{
	public:
		auto operator()(int n) { return n % 3 == 0; }
	};
	auto p3 = std::find_if(v.begin(), v.end(),  CompilerGeneratedName1() ); 
	
	// 지역변수를 캡쳐한 람다 표현식의 원리
	class CompilerGeneratedName2
	{
		int k;	// 캡쳐한 값을 보관하기 위한 멤버 데이터
	public:
		CompilerGeneratedName2(int v) : k(v) {}
		auto operator()(int n) { return n % k == 0; }
	};
	auto p4 = std::find_if(v.begin(), v.end(),  CompilerGeneratedName2(k) ); 

}
