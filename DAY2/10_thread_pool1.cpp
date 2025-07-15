#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

// 아래 코드는 무한 루프를 돌면서, 스레드를 생성합니다.
// => 네트워크 서버 라고 생각해 보세요

// 아래 처럼 필요 할때 마다 계속 스레드를 생성/파괴 하면
// #1. 스레드의 생성/파괴에는 시간이 많이 소요 됩니다.
//    (스택메모리할당/해지, OS 내부의 Thread 관리 구조체(TCB) 생성파괴)

// #2. 스레드 갯수 제한이 없습니다.
// => 수십~수백개의 스레드를 만드는 것은 오히려 성능저하..

// 해결책
// => 적절한 수의 스레드를 미리 만들고, 재워(대기상태) 놓았다가
// => 필요하는 깨워서 사용
// => 작업을 마치면 종료 시키지 말고, 다시 대기 상태로!!

// => 스레드 갯수 이상의 작업이 필요하면 "작업 Q 를 만들어서 보관"

// 스레드 풀 개념!!
// 구현은 다음 소스 부터

int main()
{
	while (true)
	{
		getchar();

		std::thread t(foo);
		t.detach();
	}
}

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
