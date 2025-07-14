#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
    return a + b;
}
int main()
{
	// 핵심 : std::async 의 launch option

 // std::future<int> ft = std::async( std::launch::async,    add, 10, 20); // 새로운 스레드로 add 실행
//	std::future<int> ft = std::async( std::launch::deferred, add, 10, 20); // 지연된 실행
									// => 새로운 스레드가 아닌 주스레드가 실행하는데
									// => 결과가 필요할때 (ft.get() 할때 )  실행해 달라.


	// launch option 은 | 가능 합니다.
	// => 아래 동작방식은 STL 구현 환경에 따라 달라질수 있습니다.(표준문서에는 이렇게 설명)
	// => 그런데, 대부분의 경우는
	// OS 가 스레드를 지원하면  : async (스레드 생성)
	// OS 가 스레드를 지원못하면 : deferred (스레드 생성 안됨)
	//std::future<int> ft = std::async( std::launch::async | std::launch::deferred, add, 10, 20);


	// launch option 을 생략시 : std::launch::async | std::launch::deferred 로 전달

	std::future<int> ft = std::async( add, 10, 20);



    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    int ret = ft.get();

    std::cout << "result : " << ret << std::endl;
}

// C++에서 스레드를 만드는 근본적인 방법은 한개 입니다.
// => std::thread

// std::thread : 사용자가 직접 스레드를 생성하는것 
// std::async  : 이 함수가 내부적으로 "std::thread" 사용 ( 정확히는 std::thread + thread pool 기술)

// promise model       : 사용자가 std::thread 로 스레드를 직접 생성
// packaged_task model : 사용자가 std::thread 로 스레드를 직접 생성
// std::async          : 사용자가 std::thread 사용 안함.
//						 std::async 함수가 내부적으로 "std::thread" 사용

// effective modern C++
// => 간단한 스레드 생성은 "std::thread" 보다 "std::async" 가 좋다.
// => 간결하고 대부분의 환경에 성능도 더 좋다.(thread pool 기술이기 때문에)