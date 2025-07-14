#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo : " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    }
}

int main()
{
//  foo(); // 새로운 실행흐름이 아닌, 주스레드가 수행

	// #1. 스레드 생성
	std::thread t(&foo); // 새로운 실행흐름(스레드)를 생성해서 foo 를 실행
						 // 이 순간 바로 실행됩니다.
						 // t.start() 같은 함수 없습니다.
}

