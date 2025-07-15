#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

std::shared_mutex m;	
	
int share_data = 0;

void Writer()
{
    while (1)
    {
		{
			// 핵심 #1. m.lock()/m.unlock() 을 직접 하지 말고, std::lock_guard 사용
			std::lock_guard<std::shared_mutex> g(m);
        	// m.lock();
			share_data = share_data + 1;
			std::cout << "Writer : " << share_data << std::endl;
			std::this_thread::sleep_for(1s);
        	//m.unlock();
		}
        std::this_thread::sleep_for(10ms);
    }
}

void Reader(std::string_view name)
{
    while (1)
    {
		{
			//std::lock_guard<std::shared_mutex> g(m); // 생성자/소멸자에서 lock/unlock 수행
			std::shared_lock<std::shared_mutex> g(m);  // 생성자/소멸자에서 lock_shared/unlock_shared 수행
			// m.lock_shared();
			std::cout << "Reader(" << name << ") : " << share_data << std::endl;
			std::this_thread::sleep_for(500ms);
			// m.unlock_shared();
		}
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
	std::thread t3(Reader, "B");
	std::thread t4(Reader, "C");
    t1.join();
    t2.join();
	t3.join();
	t4.join();
}



