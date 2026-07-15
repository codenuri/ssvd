#include <iostream>
#include <thread>
#include <atomic>

// int, long 대신 std::atomic<int>, std::atomic<long> 사용
//std::atomic<int> x{ 0 };
std::atomic<int> x = 0;

void foo()
{
    for (int i = 0; i < 1'000'000; ++i)
    {
//		x.fetch_add(1); // 내부적으로 "lock inc" 등의 기계어 코드를 사용해서 구현
						// std::mutex 등을 사용하지 않고 CPU 가 제공하는 기술(lock-free)로 구현
//      ++x;  // x.operator++() 함수 호출, 결국 내부적으로는 위와 유사

		// 단, fetch_add() 사용시 2번 인자로 std::memory_order 를 지정해서 세밀한 조정가능
		// => 목적에 따라 좀더 효율적인 기계어 코드를 만들수 있다.
		x.fetch_add(1, std::memory_order_relaxed); 
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

// 정리
// int, long 등의 기본 타입에 대한 단순 연산을 동기화(+, - 등)
// => std::atomic<>

// 단순 연산이 아닌 task 기반(파일 작업, 프린터 작업)
// => std::mutex

