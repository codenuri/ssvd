#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// 반환값

int add(int a, int b)
{
    std::cout << "start add" << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "finish add" << std::endl;
    return a + b;
}

int main()
{
	// #1. 아래 코드 실행해서 결과(화면 로그)를 예측해 보세요
	// => continue main 결과
    std::future<int> ft = std::async( std::launch::async, add, 10, 20);

    std::cout << "continue main " << std::endl;

    int ret = ft.get();

    std::cout << "finish main" << std::endl;
}



