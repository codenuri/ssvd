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
	// 아래 코드의 화면 출력 결과를 예측해 보세요
	// => 새로운 스레드로 실행하므로 "add" 종료를 대기하지 않고 "continue main" 출력
//  std::future<int> ft = std::async( add, 10, 20);	// A. std::async() 반환 값을 받은 경우
  	std::async( add, 10, 20);						// B. std::async() 반환 값을 받지 않은 경우
													// => add 가 종료되어야지 아래코드 실행
													// => 마치 동기 호출 처럼 보입니다
													// => 하지만 스레드를 생성한것 맞습니다.
													// => 이유는 다음예제에서.. 

	std::cout << "continue main " << std::endl;

//  int ret = ft.get();

    std::cout << "finish main" << std::endl;
}



