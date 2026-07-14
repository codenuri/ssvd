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
template<typename T> 
void sum(T first, T last, unsigned long long& result)
{
    result = std::accumulate(first, last, result);
}

template<typename T> 
void parallel_sum(T first, T last, unsigned long long& result)
{
	unsigned long long cnt_elements = std::distance(first, last); 

	// 몇개의 스레드를 만들것인가 ?? 가장 중요한 문제

	unsigned long long cnt_threads = 4; 

    unsigned long long block_size = cnt_elements / cnt_threads;

	//--------------------------------
	std::vector<std::thread> v;
	std::vector<unsigned long long> result_vector(cnt_threads); 

	T start = first;

	for( int i = 0; i < cnt_threads - 1; i++ )
	{
		T end = std::next( start, block_size);

		v.emplace_back( &sum<T>, start, end, std::ref(result_vector[i]));		

		start = end;
	}
	sum(start, last, result_vector[cnt_threads-1]);

	for( auto& t: v)
		t.join();

	result = std::accumulate( result_vector.begin(), result_vector.end(), 0);
}

int main()
{
	init();

    unsigned long long s = 0;
    parallel_sum(v.begin(), v.end(), s);
	
	std::cout << s << std::endl;
}
