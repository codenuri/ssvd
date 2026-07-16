#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
#include <execution>
#include <syncstream>

int main()
{
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

	// vector 의 모든 요소의 합을 구하는 코드
	int s = 0;
// 	std::for_each(v.begin(), v.end(), [&s](int n) { s += n;} ); 


	// [핵심]
	// 병렬 버전 사용시 합을 저장하는 변수는 동기화 되어야 합니다.
	// => mutex 또는 atomic	

	// 잘못된 코드
 //	std::for_each(std::execution::par, v.begin(), v.end(), [&s](int n) { s += n;} ); 

	// #1. mutex 로 해결
	std::mutex m;
 	std::for_each(std::execution::par, v.begin(), v.end(), [&s, &m](int n) 
							{
								std::lock_guard<std::mutex> g(m);
								 s += n;
							} ); 


	// #2. 결과를 담은 공유 변수(s) 를 atomic 으로 
	std::atomic<int> s2 = 0;
	std::for_each(std::execution::par, v.begin(), v.end(), [&s2](int n) {s2 += n;});

	std::cout << "result: " << s << '\n';

}
