#include <iostream>
#include <thread>
#include <windows.h> // <= windows API 사용을 위해
#include <chrono>
using namespace std::literals;

// 스레드 우선 순위
// => windows, linux, osx 등의 대부분의 OS 에는 "스레드 우선순위" 라는 개념이 있습니다.
// => 이런 개념이 없는 OS도 있습니다.

// => C++ 표준 라이브러리에서 스레드 우선순위를 설정하는 방법은 없습니다.
// => 대신 OS 레벨의 스레드 핸들을 얻을수 있습니다.
// => 핸들을 구한후 OS 레벨이 시스템 콜을 직접 사용가능합니다.


void foo()
{
    auto tid = std::this_thread::get_id(); 
}

int main()
{
    std::thread t(&foo);

	// #1. OS 레벨의 핸들 얻기
	std::thread::native_handle_type h = t.native_handle(); 
							// windows : HANDLE 이라는 타입
							// linux   : pthread_t 타입
	
	// 이제 각 OS 별 시스템 콜을 사용하면 됩니다.
	// => 아래 코드는 windows OS 에서 스레드 우선순위를 최고로 설정하는 코드
	// => windows OS 에서만 빌드 가능
	SetThreadPriority((HANDLE)h, THREAD_PRIORITY_TIME_CRITICAL);



    t.join();
}

