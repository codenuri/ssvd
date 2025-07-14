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



