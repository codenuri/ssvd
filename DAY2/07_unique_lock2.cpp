#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::timed_mutex m;

int main()
{
    std::unique_lock<std::timed_mutex> u1;
    std::unique_lock<std::timed_mutex> u2(m);

	// std::unique_lock 역시 "복사 는 안되고", "이동만 가능" 한 타입
	// => 스레드 관련 대부분 클래스의 특징

    u1 = u2; 			// error
    u1 = std::move(u2); // ok 

	// lock 여부를 확인 하는 방법 
	// #1. 멤버 함수 사용
    std::cout << u1.owns_lock() << std::endl; 

	// #2. if 로 직접 조사도 가능
    if (u1)
        std::cout << "acquire" << std::endl;

	// 명시적 unlock()가능도 가능
    u1.unlock();

    std::cout << u1.owns_lock() << std::endl;  

    if (u1.try_lock_for(2s))
    {
        //....
        u1.unlock();
    }

	// unlock 이 아닌. mutex 자체의 연결을 해제!
	// u1.unlock() : u1 이 보관하는 mutex 를 unlock
	// u1.unlock() : u1 이 보관하는 "mutex = 0" 즉, 뮤텍스 관계 해제.
    u1.release();
}



