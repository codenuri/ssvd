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

	bool operator()(int n) { return value % k == 0; }
};

int main()
{
	std::vector<int> v = {1,2,3,4,5,6};

	int k = 3;

	IsModulus m(k);
	bool b = m(10);


	auto p1 = std::find_if(v.begin(), v.end(), ??? ); 

}