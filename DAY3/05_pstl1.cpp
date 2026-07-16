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

	// 스레드 갯수등을 지정할수는 없습니다.
	// 구현 원리도 컴파일러 마다 다릅니다(버전에 따라 변경될수 있음)
	// g++ : TBB 라이브러리 재사용
	// cl  : windows os 의 thread pool 사용

	// 세부적인 제어가 필요하면 
	// 직접 구현하세요 - 1일차. paralled_sum() 같이 만들면 됩니다.

	// C++ 표준에서 Thread Pool 등을 지원하면 안되나요 ?
	// => 시도가 있었습니다.
	// => 그런데, 지금은 "Thread Pool" 은 옛날기술..
	// => 훨씬 훌륭하게 추상화면 "std::execution" 이 C++26 에서 도입예정
	//    현재 "ndvia" 개발자 중 C++ 표준 위원이 설계중.. 
	// => 현재 ndvia C++ 컴파일러만 사용가능 
}

// 주의 : windows os 에서 mingw 사용시
// => libc++ 이 parallel stl 을 지원하지 못할수 있습니다.
