#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <stdatomic.h>  // C11 atomic 관련 표준 함수
						// C++ 은 C++23 부터 지원
std::mutex m;
//long x = 0;
atomic_int x = 0;


void foo()
{
    for (int i = 0; i < 100000; ++i)
    {
		// 방법 #1. mutex 를 사용해서 동기화
		// => +1 등의 작업을 위해 std::mutex 를 사용하는것은 오버헤드가 크다.
		/*
		m.lock();
        ++x; // x = x+1
		m.unlock();
		*/

		// 방법 #2. CPU 가 제공하는 안전하게 1을 증가하는 기계어 명령 사용
		// => "lock-free" 기술
		// => 동기화를 위해서 OS 레벨의 도구가 아닌 CPU가 제공하는 도구를 사용하는것
		// => mutex 를 사용하는 것 보다 훨씬 빠르게 동작
		// lock inc x;

		// 방법 #3. 위 기계어 코드로 구현된 C/C++표준 함수 사용
		// => <stdatomic.h> 헤더 필요
		// => C 언어는 C11 부터 지원
		// => C++ 언어는 C++23 부터 지원( std::atomic<> 이 있어서 초기 지원 안함)
		// => g++ 소스.cpp -std=c++23 필요
		atomic_fetch_add(&x, 1);

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
