#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;	    // lock(), try_lock()
std::timed_mutex m;	// lock(), try_lock()
					// try_lock_for(시간동안), try_lock_until(시간까지)

int share_data = 0;

void foo()
{
    //m.lock();				// 획득 못하면 대기
    // if ( m.try_lock() )		// 획득 못하면 false 반환, 대기 안함
	if ( m.try_lock_for(2s) )	// 획득 못하면 2초간 대기, 2초후 false 반환
    {
        share_data = 100;
        std::cout << "using share_data" << std::endl;
        std::this_thread::sleep_for(3s);
        m.unlock();
    }
    else
    {
        std::cout << "뮤텍스 획득 실패" << std::endl;
    }
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}

// C++ 표준 뮤텍스는 6개 입니다.

// std::mutex,			std::recursive_mutex,			std::shared_mutex
// std::timed_mutex,	std::timed_recursive_mutex,		std::timed_shared_mutex


