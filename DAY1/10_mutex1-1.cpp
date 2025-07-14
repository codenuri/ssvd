#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;

void delay() { std::this_thread::sleep_for(10ms); }


std::mutex m; // 공유자원 "x" 를 보호하기 위한 mutex

void foo(std::string_view name)
{
	static int x = 0;

    for (int i = 0; i < 10; i++)
    {
		// 아래 공간은 한개의 스레드씩 실행되어야 합니다.
		// => 여러 스레드가 동시 실행하면 안됩니다.
		// => 임계영역(critical section) 이라고 합니다.
		
		m.lock(); 
		//---------------------		
        x = 100;   delay();
        x = x + 1; delay();
        std::cout << name << " : " << x << std::endl; delay();
		//--------------------
		m.unlock();
    }
}

int main()
{
    std::thread t1(foo, "A");
    std::thread t2(foo, "\tB");
    t1.join();
    t2.join();
}



