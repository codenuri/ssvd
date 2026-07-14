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

	// 몇개의 스레드를 만들것인가 ?? 가장 중요한 문제
	// 고려할점 #1 : 현재 CPU 가 실제 몇개의 코어를 지원하는 가(실제 동시에 실행 가능한 스레드 수)
	// 고려할점 #2 : 데이터 갯수, 데이터가 작으면 그냥 한개의 스레드가 더 좋다

	unsigned long hw_cnt_thread = std::thread::hardware_concurrency();

	if ( hw_cnt_thread == 0 ) // 스레드 갯수가 0이 아니라, 위 함수를 지원 못하는 환경
		hw_cnt_thread = 2;

	unsigned long min_cnt_per_thread = 1'000; // 한개 스레드가 처리할 최소 데이터 갯수
											  // 1000 보다 작으면 단일 스레드

	unsigned long sw_thread = ( cnt_elements + min_cnt_per_thread -1 ) / min_cnt_per_thread;
								// (전체 요소 갯수 + 스레드당최소 갯수 -1 ) / 스레드당 갯수

	// 실제 스레드 갯수는 hw 적인 갯수와 최소 데이터에 의한 갯수중 작은 것
	unsigned long long cnt_threads = std::min(hw_cnt_thread,  sw_thread);

	// 한글 출력 깨지면 : 터미널에서 "chcp 65001" 한번 실행하세요
	std::cout << "hw 스레드 갯수 : " << hw_cnt_thread << std::endl;
	std::cout << "요소갯수에 의한  스레드 갯수 : " << sw_thread << std::endl;
	std::cout << "최종  스레드 갯수 : " << cnt_threads << std::endl;



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

//	result = std::accumulate( result_vector.begin(), result_vector.end(), 0);
			// 0 : int 타입 이므로 accumulate 가 내부적으로 합을 보관하는 변수로 int 변수 사용
			//	   오버 플로우 발생
	result = std::accumulate( result_vector.begin(), result_vector.end(), 0ULL);		
															// (unsigned long long)0
}

int main()
{
	init();

    unsigned long long s = 0;
    parallel_sum(v.begin(), v.end(), s);
	
	std::cout << s << std::endl;
}

/*
// C++ 표준 accumulate() 의 원리
template<typename ITER, typename T>
R accumulate(ITER first, ITER last, T init)
{
	// 결과값 담을 변수의 타입은 초기값의 타입과 동일(T)
	T s = init;

	// first ~ last 의 모든 요소의 합을 s 에 담는다
}
*/