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

}




int main()
{
	init();

    int s = 0;
    
	//sum(v.begin(), v.end(), s);
	parallel_sum(v.begin(), v.end(), s);

    std::cout << s << std::endl;
}
