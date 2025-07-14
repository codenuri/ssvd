#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;

void delay() { std::this_thread::sleep_for(10ms); }

void foo(std::string_view name)
{
//  int x = 0;	// 지역변수, 스레드당 한개, 항상 멀티스레드에 안전하고, 예상된 결과가 나옵니다.

	static int x = 0; // static 지역변수, 모든 스레드 공유

    for (int i = 0; i < 10; i++)
    {
        x = 100;   delay();
        x = x + 1; delay();
        std::cout << name << " : " << x << std::endl; delay();
    }
}

int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "\tB");
    t1.join();
    t2.join();
}



