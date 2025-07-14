// 02_thread9-1.cpp
#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include "chronometry.h" // 성능 측정을 위한 "chronometry()" 함수가 있습니다.

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
template<typename T>
void sum(T first, T last, int& result)
{
    result = std::accumulate(first, last, result);
}

template<typename T>
void parallel_sum(T first, T last, int& result)
{
	const unsigned long cnt_element = std::distance(first, last); 

	if ( cnt_element == 0 ) return;

	const unsigned long cnt_per_thread = 25; 
	const unsigned long max_thread = (cnt_element + cnt_per_thread -1) / cnt_per_thread;


	unsigned long hw_thread = std::thread::hardware_concurrency();

	if ( hw_thread == 0) 
		hw_thread = 2;   

	const unsigned long cnt_thread = std::min(hw_thread, max_thread);
	const unsigned long block_size = cnt_element / cnt_thread; 

	std::cout << "필요한 스레드 갯수   : " << cnt_thread << std::endl;
	std::cout << "스레드당 데이타 갯수 : " << block_size << std::endl;
	//----------------------------------------------------------

	std::vector<std::thread> thread_vector(cnt_thread - 1); 
	std::vector<int> result_vector(cnt_thread);

	T start = first; 

	for( int i = 0; i < cnt_thread-1; i++)
	{
		T end = std::next(start, block_size);
		thread_vector[i] = std::thread(&sum<T>, start, end, std::ref(result_vector[i]) );
		start = end;
	}

	sum(start, last, std::ref(result_vector[cnt_thread-1]));

	for( auto& t : thread_vector)
		t.join();

	result = std::accumulate(result_vector.begin(), result_vector.end(), 0);
}






int main()
{
	init();

    int s = 0;
    
	chronometry(sum<std::vector<int>::iterator>, v.begin(), v.end(), s);
							// sum(v.begin(), v.end(), s) 의 수행 시간을 출력해 달라.

//	chronometry(parallel_sum<std::vector<int>::iterator>, v.begin(), v.end(), s);

    std::cout << s << std::endl;
}







