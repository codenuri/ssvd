#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals;

// std::this_thread::yield() : 현재 스레드의 실행 흐름을 포기(yield) 하는 함수

// 아래 코드가 sleep_for 등의 원리 입니다.
void mysleep(std::chrono::microseconds us)
{
	// #1. 목표 시간을 구하고
    auto target = std::chrono::high_resolution_clock::now() + us;

	// #2. 그 시간이 되지 않으면 현재 실행흐름 포기
    while (std::chrono::high_resolution_clock::now() < target)
        std::this_thread::yield();
}

int main()
{
    mysleep(1s);
}