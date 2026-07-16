// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

// 함수 객체의 장점

int main()
{
	std::vector<int> v = {1,2,3,4,5,6};

	// 주어진 구간에서 처음 나오는 3의 배수를 찾고 싶다
	// => std::find_if 알고리즘

	auto p = std::find_if(v.begin(), v.end(), 함수);
	

}