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

	std::vector<std::thread> thread_vector(cnt_thread - 1); // 24개 - 주스레드 = 23개
	std::vector<int> result_vector(cnt_thread);

	T start = first; // 하나의 스레드가 수행할 블럭의 시작

	for( int i = 0; i < cnt_thread-1; i++)
	{
		T end = std::next(start, block_size);

		thread_vector[i] = std::thread(sum<T>, start, end, result_vector[i]);

		start = end;
	}

	// 이제 마지막 구간(start ~ last) 은 주스레드가 수행하면 됩니다.
	sum(start, last, result_vector[cnt_thread-1]);

	// 모든 스레드 종료를 대기 합니다.
	for( auto& t : thread_vector)
		t.join();

	// 이제 각 스레드의 연산 결과는 result_vector 에 있으므로 모두 합하면 됩니다.
	result = std::accumulate(result_vector.begin(), result_vector.end(), 0);
}






int main()
{
	init();

    int s = 0;
    
	//sum(v.begin(), v.end(), s);
	parallel_sum(v.begin(), v.end(), s);

    std::cout << s << std::endl;
}
