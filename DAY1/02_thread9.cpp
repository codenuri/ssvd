#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

// 핵심 : 지금 까지 배운 내용으로 만드는 "예제"

constexpr std::size_t sz = 1'000'000;

std::vector<int> v;

void init()
{
    for (int i = 0; i < sz; ++i)
    {
        v.push_back(i);
    }
}
//------------------------------------------------------------

// 구간의 합을 구하는 함수.
void sum(int first, int last, int& result)
{
	// std::accumulate : 주어진 구간의 합을 구하는 C++ 표준 함수
	//                   마지막 인자는 합을 구할때 사용하는 sum 변수의 초기값(보통 0)
    result = std::accumulate(first, last, result);
}

int main()
{
	init();

    int s = 0;
    
	sum(v.begin(), v.end(), s);

    std::cout << s << std::endl;
}
