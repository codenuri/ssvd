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

// sum 의 병렬 버전
template<typename T> 
void parallel_sum(T first, T last, unsigned long long& result)
{
	// 요소의 갯수 구하기
//	unsigned long long cnt_elements = last - first; // bad, std::vector 는 가능하지만 std::list 는 안됨
	unsigned long long cnt_elements = std::distance(first, last); // good

	// 스레드 개수
	unsigned long long cnt_threads = 4; // 최적화된 갯수를 구하는 것이 이번 예제의 핵심

	// 스레드당 요소의 갯수
    unsigned long long block_size = cnt_elements / cnt_threads;

	//--------------------------------
	std::vector<std::thread> v;
	std::vector<unsigned long long> result_vector(cnt_threads); // 각 스레드의 결과를 담을 vector

	T start = first;

	for( int i = 0; i < cnt_threads - 1; i++ )
	{
		T end = std::next( start, block_size);

		// sum 자체가 단일 스레드로 구간의 합을 구하므로
		// sum 사용, 단, template 이므로 &sum 가 아닌 &sum<T>
		v.emplace_back( &sum<T>, start, end, std::ref(result_vector[i]));		

		start = end;
	}
	// 마지막 구간은 주스레드가 수행
	sum(start, last, result_vector[cnt_threads-1]);

	// 모든 스레드 종료 대기
	for( auto& t: v)
		t.join();

	// 각각의 결과를 합
	result = std::accumulate( result_vector.begin(), result_vector.end(), 0);
}

int main()
{
	init();

    unsigned long long s = 0;
    parallel_sum(v.begin(), v.end(), s);
	
	std::cout << s << std::endl;
}
