#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
#include <execution>
#include <syncstream>

void foo(int n)
{
    std::osyncstream out(std::cout);
    out << "[" << std::this_thread::get_id() << "]: " << n << '\n';
}

int main()
{
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

	// for_each 알고리즘 - C++98 부터 제공된 표준 알고리즘(함수)
	// => "인자로 전달된 구간의 모든 요소"를 차례대로 foo 에전달
//  std::for_each(v.begin(), v.end(), foo); // foo 는 요소의 갯수(10) 만큼 호출 

	// C++17 부터 70여개의 표준 알고리즘이 병렬 버전을 지원 합니다(스레드 버전)
	// 1번째 인자로 실행 방법 전달 가능
	// std::execution::seq : 단일 스레드 (생략가능)
	// std::execution::par : 다중 스레드 
//	std::for_each(std::execution::seq, v.begin(), v.end(), foo); // 싱글
	std::for_each(std::execution::par, v.begin(), v.end(), foo); // 싱글
}