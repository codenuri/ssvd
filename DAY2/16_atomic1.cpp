#include <iostream>
#include <thread>
#include <mutex>
#include "chronometry.h"

constexpr unsigned int cnt = 1'000'000;


long x = 0; // 전역변수, 모든 스레드가 공유.

void foo()
{
    for (int i = 0; i < cnt; ++i)
    {
        x = x + 1;  
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
	// "x = x + 1" 이 안전하게 실행되었다면 아래 결과는 3'000'000 이어야 합니다.
    std::cout << x << std::endl;
}
