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

    u1 = u2; 			// error. 복사는 안됨
    u1 = std::move(u2); // ok.   이동은 가능

	// u1이 관리하는 mutex 가 lock 이 되었는지 조사 방법 2가지
    std::cout << u1.owns_lock() << std::endl; 	// #1

    if (u1)		// #2
        std::cout << "acquire" << std::endl;

    u1.unlock();

    std::cout << u1.owns_lock() << std::endl;  // false

    if (u1.try_lock_for(2s))
    {
        //....
        u1.unlock();
    }
//	u1.unlock();	  // unlock 만, mutex 와는 계속 연결(내부적으로 참조로 보관)
    u1.release();	  // mutex 와 연결해지!!
}

// 권장 
// 기본 사용 : std::lock_guard
// condition_variable 과 같이 사용하려면 : std::unique_lock 필요

