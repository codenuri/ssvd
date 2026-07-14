#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
using namespace std::literals;

// native_handle_type 이야기
// => 스레드 우선 순위

// Windows OS 에는 thread priority 라는 개념이 있습니다.
// 다른 OS 는 priority 개념이 없을수도 있습니다.
// => 그래서, C++ 표준의 std::thread 는 "우선순위"를 지원하는 멤버가 없습니다
// => 이경우, C++ 표준시 priority 를 사용하려면 native handle 을 얻어야 합니다.
void foo()
{
    auto tid = std::this_thread::get_id(); 
}

int main()
{
    std::thread t(&foo);

	// #1. std::thread 가 내부적으로 관리하는 OS 의 스레드 핸들 얻기
	std::thread::native_handle_type h = t.native_handle();

	// #2. h 를 각 OS 의 시스템콜에 전달하면 됩니다.
	SetThreadPriority((HANDLE)h, THREAD_PRIORITY_TIME_CRITICAL);

	// 단, 위와같이 코드를 작성하면 코드의 호환성이 부족해집니다.

    t.join();
}

