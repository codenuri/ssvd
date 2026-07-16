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

// C++ 표준관련
// 2003 년에 N/W 오픈소스인 Asio 라는 것이 있었는데, 아주 잘만들어진 라이브러리
// => Asio 를 C++11 N/W 표준 라이브러리로 채택하자..
// => Asio 의 스레드 풀과 비동기 기술이 아주 좋다!!

// 그러다가 "NDVIA" 일부 개발자가 다른 방식을 주장
// => 단순 N/W 관련이 아닌 범용적 용도의 스레드/비동기 관리 기술을 만들자
// => 채택!!
// => C++26 의 std::execution
// => C++29 에 std::execution 과 연동되는 N/W 표준 예상됨. 