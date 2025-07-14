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
	std::future<int> ft = std::async( std::launch::deferred, add, 10, 20); // 지연된 실행
									// => 새로운 스레드가 아닌 주스레드가 실행하는데
									// => 결과가 필요할때 (ft.get() 할때 )  실행해 달라.

    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    int ret = ft.get();

    std::cout << "result : " << ret << std::endl;
}



