#include <iostream>
#include <thread>
#include <atomic>


std::atomic<int> x = 0; // std::atomic<Type>
						// => 모든 멤버 함수가 atomic 연산(CPU 가 제공하는 동기화 도구)
						//    사용. 

void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
//		x.fetch_add(1);  // 안전하게 1증가
        ++x; 			 // 이렇게 해도 위와 동일
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

