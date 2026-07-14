#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
//------------------------------------
// 전역 vector 를 초기화 하는 코드
constexpr std::size_t sz = 1'000'000;
std::vector<int> v;

void init()
{
    for (int i = 0; i <= sz; ++i)
    {
        v.push_back(i);
    }	
}
//-------------------------------------------
// 구간의 합을 구하는 함수.
// => 반복자를 받아서 모든 요소의 합을 구한후, 3번째 인자로 전달된 참조에 결과를 담아 주는 함수
template<typename IT, typename RT> 
void sum(IT first, IT last, RT& result)
{
    result = std::accumulate(first, last, result);
}

int main()
{
	init();

    unsigned long long s = 0;
    sum(v.begin(), v.end(), s);	// v의 모든 합을 s 에 담는 코드

    std::cout << s << std::endl;
}
