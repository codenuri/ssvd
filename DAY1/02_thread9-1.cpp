// 02_thread9-1.cpp
#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

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

// 단일 스레드로 구간의 합을 구하기
template<typename T>
void sum(T first, T last, int& result)
{
    result = std::accumulate(first, last, result);
}

// 다중 스레드로 구간의 합을 구하기.
template<typename T>
void parallel_sum(T first, T last, int& result)
{
    // #1. 요소의 갯수 파악
//	const unsigned long cnt_element = last - first; // vector, 배열등의 연속된 메모리는 가능
													// list 등의 반복자라면 error

	const unsigned long cnt_element = std::dist(first, last); // ok. 좋은 코드!!

	if ( cnt_element == 0 ) return 0;

	

}






int main()
{
	init();

    int s = 0;
    
	sum(v.begin(), v.end(), s);

    std::cout << s << std::endl;
}
