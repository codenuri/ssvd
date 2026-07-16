// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

// 함수 객체의 장점
bool foo(int n) { return n % 3 == 0; }

int main()
{
	std::vector<int> v = {1,2,3,4,5,6};

	// 주어진 구간에서 처음 나오는 3의 배수를 찾고 싶다
	// => std::find_if 알고리즘
//	auto p = std::find_if(v.begin(), v.end(), 함수); // 여기서 함수는 인자가 한개이어야 합니다
													 // "단항 함수"
	auto p = std::find_if(v.begin(), v.end(), foo); 
	std::cout << *p << std::endl;

	// 이제 아래 주석을 생각해 보세요...
	// 주어진 구간에서 처음 나오는 k의 배수를 찾고 싶다
	// ??? 함수를 어떻게 만들어야 할까요 ?
	// => foo 안에서 "3" 대신 "k" 를 사용해야 하는데, k는 main 의 지역변수
	// => foo 는 반드시 인자 한개로 해야 하므로 k 를 전달할수도 없습니다.
	int k = 3;
	auto p1 = std::find_if(v.begin(), v.end(), ??? ); 

	// 해결책
	// => 일반 함수로는 쉽지 않지만, 함수 객체로 하면 간단합니다.
}