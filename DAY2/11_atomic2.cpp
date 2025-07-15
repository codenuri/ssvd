#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

std::mutex m;
long x = 0;


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
		// 
		// lock inc x;

		// 방법 #3. 위 기계어 코드로 구현된 C/C++표준 함수 사용
		std::fetch_and_add(&x, 1);

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
