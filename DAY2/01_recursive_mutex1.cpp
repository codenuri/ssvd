#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m; // mutex 소유자가 다시 lock 할수 없습니다.
			    // 여러번 lock 안됨

std::recursive_mutex m; // 여러번 lock 가능.
						// 단, lock 횟수 만큼 unlock 해야 한다.

int share_data = 0;

void foo()
{
    m.lock();
	m.lock();

    share_data = 100;
    std::cout << "using share_data" << std::endl;
    m.unlock();
	m.unlock();
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}




