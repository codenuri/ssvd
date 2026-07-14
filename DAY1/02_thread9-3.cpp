#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include "chronometry.h"

//------------------------------------
// 복습 하실때..
// 아래 2개 변수의 값을 변경하면서 성능을 확인해 보세요
// => 데이터 양이 적다면 "단일 스레드" 가 좋습니다
// => 데이터 양이 많다면 "멀티 스레드" 가 좋습니다
//    단, 스레드 갯수도 충분히 고려되어야 합니다.
constexpr std::size_t sz = 10'000'000;

// 스레드 수를 결정하기 위한 목표 작업 단위
// 1. 요소 갯수 min_cnt_per_thread 이하라면 스레드 생성안함
// 2. 이상이라면 "요소갯수 / min_cnt_per_thread" 의 스레드갯수가 후보
// 3. 최종 개수는 hw 고려
unsigned long min_cnt_per_thread = 1000'000;


std::vector<int> v;

void init()
{
	for (int i = 1; i <= sz; ++i)
	{
		v.push_back(i);
	}
}
//-------------------------------------------
template<typename T>
void sum(T first, T last, unsigned long long& result)
{
	result = std::accumulate(first, last, result);
}

template<typename T>
void parallel_sum(T first, T last, unsigned long long& result)
{
	unsigned long long cnt_elements = std::distance(first, last);
	unsigned long hw_cnt_thread = std::thread::hardware_concurrency();

	if (hw_cnt_thread == 0) 
		hw_cnt_thread = 2;


	unsigned long sw_thread = (cnt_elements + min_cnt_per_thread - 1) / min_cnt_per_thread;
	unsigned long long cnt_threads = std::min(hw_cnt_thread, sw_thread);
	unsigned long long block_size = cnt_elements / cnt_threads;

	std::cout << "thread count : " << cnt_threads << std::endl;

	//--------------------------------
	std::vector<std::thread> v;
	std::vector<unsigned long long> result_vector(cnt_threads);

	T start = first;

	for (int i = 0; i < cnt_threads - 1; i++)
	{
		T end = std::next(start, block_size);

		v.emplace_back(&sum<T>, start, end, std::ref(result_vector[i]));

		start = end;
	}
	sum(start, last, result_vector[cnt_threads - 1]);

	for (auto& t : v)
		t.join();

	result = std::accumulate(result_vector.begin(), result_vector.end(), (unsigned long long)0);
}

void single_thread()
{
	unsigned long long s = 0;
	sum(v.begin(), v.end(), s);
	std::cout << s << std::endl;
}

void multi_thread()
{
	unsigned long long s = 0;
	parallel_sum(v.begin(), v.end(), s);
	std::cout << s << std::endl;
}

int main()
{
	init();

	chronometry(single_thread);
	chronometry(multi_thread);
}
