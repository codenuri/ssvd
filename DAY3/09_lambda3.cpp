// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

// 인자가 한개인 일반 함수
bool foo(int n) { return n % 3 == 0; }	

// 인자가 한개인 함수 객체
struct IsModulus 
{
	int value;		// 핵심 : 멤버 데이타를 가질수 있다
	IsModulus(int v) : value(v) {}

	bool operator()(int n) { return n % value  == 0; }
};

int main()
{
	std::vector<int> v = {1,2,3,4,5,6};

	int k = 3;

	IsModulus m(k);	 // m 은 객체 입니다. 생성자로 전달한 k 값을 내부 멤버에 보관(value)
	bool b = m(10);  // m 은 객체지만 단항함수 처럼 사용가능(인자가 한개인 함수)
					 // bool b = 10 % value(결국 k) 입니다.
					 // 결국 m 은 단항함수지만 k 값 보관 하고 있습니다

	auto p1 = std::find_if(v.begin(), v.end(), m );  // ok
						// 결국 k 값을 보관(캡쳐)한 단항함수를 전달하는 코드
}
// 일반 함수 : 동작만 할수 있습니다.
// 함수 객체 : 동작 + 자신이 속한 문맥(main) 의 지역변수를 캡쳐해서 사용가능합니다
//          => 상태(멤버데이터) 가 있기 때문에 가능.

// 그래서
// => 함수 객체를 "상태를 가지는 함수" 라고 합니다.