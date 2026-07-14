#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// printf() 도 반환값이 있습니다 => int printf(const char* fmt, ... )
// => 하지만 대부분 반환값을 받지 않습니다.
// => 반환값 보다는 printf의 동작 자체가 중요하므로


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
	// 설계에 담긴 철학
	// std::async() 호출시 반환된 future 의 소멸자에서 get() 하지 않으면 어떻게 될까요 ?

  	std::async( add, 10, 20); // 여기서 add()종료를 대기 하지 않으면
							  
	// 주스레드는 바로 종료됩니다.
	// => 그러면 위에서 생성된 스레드는 강제 종료 됩니다.
	// => 그래서 async() 는 안전하게 실행됨을 보장하고 싶었습니다.

	std::future<int> ret =std::async( add, 10, 20); // 여기서는 add()대기 안함.

}	// <= ret 파괴. 이때 get() 하므로 add() 스레드 가 종료될때를 대기

// 결론 
// 1. async() 반환 값을 받으면 "반환값 ret" 가 파괴 될때 get()으로 자동 대기
// 1. async() 반환 값을 안 받으면 임시객체의 파괴(async()문장끝)시 대기

