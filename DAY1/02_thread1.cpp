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

	// #2. 주의
	// 스레드를 생성한 경우 아래 2개중 한개 작업을 반드시 해야 합니다
	// 1. 새로운 스레드 대기 - join
	// 2. 새로운 스레드와 분리- detach

//	t.join(); // 새로운 스레드가 종료될때를 대기 ( linux : pthread_join() )
	t.detach(); // 자식 스레드와 분리
			    // 대기 하지 않고, 주스레드는 계속 실행

	std::cout << "main 계속 실행\n";
}
// 주 스레드 가 종료 되면
// => 기존에 수행중이던 스레드가 있다면
// => 강제 종료 됩니다. - C++ 특징
// => C# 등의 언어는 새로운 스레드를 대기..



// 실행시 한글을 깨지만
// 터미널에서 chcp 65001 한번 실행해 주세요