#include <iostream>
#include <chrono>
#include <thread>
using namespace std::literals;

// std::this_thread::yield() 
// => 현재 스레드의 남은 실행 시간을 양보

// 아래 함수
// => 무한 루프에서 주기적으로 깨어 나서
//    시간을 확인후, 아직 목표 시간이 안됬으면 실행흐름 양보
//    sleep() 을 직접 구현한것
void mysleep(std::chrono::microseconds us)
{
    auto target = std::chrono::high_resolution_clock::now() + us;

    while (std::chrono::high_resolution_clock::now() < target)
	{
        std::this_thread::yield(); // 목표 시간이 안되었으면 더이상 CPU 사용하지 말고
									// 다른 스레드에게 양보
	}
}

int main()
{
    mysleep(1s);
}