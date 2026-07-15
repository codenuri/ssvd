#include <iostream>
#include <thread>
#include <atomic>

long x = 0;

std::mutex m;

void foo()
{
    for (int i = 0; i < 1'000'000; ++i)
    {
		// 해결책 #1. std::mutex 사용
		m.lock();
        ++x; 
		m.unlock();
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
    std::cout << x << std::endl;
}
