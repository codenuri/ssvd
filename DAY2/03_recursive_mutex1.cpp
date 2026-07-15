#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

//std::mutex m;	// 한번만 lock() 가능
				// lock() 으로 소유권 획득후 다시 lock() 할수 없다

std::recursive_mutex m;	// 소유자가 다시 lock 할수 있다.
						// 여러번 lock() 가능
						// 단, lock() 횟수 만큼 unlock() 해야 한다


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
    std::jthread t1(foo);
    std::jthread t2(foo);
}




