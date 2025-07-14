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

	const unsigned long cnt_element = std::distance(first, last); // ok. 좋은 코드!!

	if ( cnt_element == 0 ) return;

	// #2. 요소의 갯수로 스레드갯수 결정
	const unsigned long cnt_per_thread = 25; // 한개당 최소 25개 수행
	const unsigned long max_thread = (cnt_element + cnt_per_thread -1) / cnt_per_thread;
					// => 요소가 90개라면 4개 스레드 필요
					// => 요소가 900개 라면 40개 스레드 필요


	// #3. 현재 PC 의 코어의 갯수를 구합니다.
	unsigned long hw_thread = std::thread::hardware_concurrency();

	if ( hw_thread == 0) // 혹시 위 함수의 구현이 제공되지 않으면
		hw_thread = 2;   // 최대 2개

	// #4. 이제 실제 필요한 스레드의 수를 계산합니다.
	// => 결국, 스레드 프로그램의 핵심중의 하나는 "몇개" 를 만들것인가!! 중요합니다.
	const unsigned long cnt_thread = std::min(hw_thread, max_thread);

	const unsigned long block_size = cnt_element / cnt_thread; 


	std::cout << "필요한 스레드 갯수   : " << cnt_thread << std::endl;
	std::cout << "스레드당 데이타 갯수 : " << block_size << std::endl;

}

// 인텔 최신 CPU(P core 개념, 2021.10월 발표)
// => 위 코드를 사용해도 나쁘지 않음..
// => 그런데, 정말 최적화 하려면 부하가 큰 작업은 P core 에서만 실행
// 1. P Core 만의 갯수 구하기 => C++ 표준 지원 안함,
//                             각 OS 의 시스템 콜 사용(windows 는 11 이후만 가능)

// 2. 생성된 스레드를 P core 에서만 실행되도록 => C++ 지원 안함
// => 단, 각 OS 의 시스템 콜로 제공됨
// Windows : SetThreadAffinityMask
// Linux : sched_setaffinity







int main()
{
	init();

    int s = 0;
    
	//sum(v.begin(), v.end(), s);
	parallel_sum(v.begin(), v.end(), s);

    std::cout << s << std::endl;
}
