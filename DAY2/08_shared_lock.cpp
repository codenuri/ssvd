// 02_shared_mutex2  복사
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

// std::lock_guard  : 생성자에서 lock(), 소멸자에서 unlock()
// std::shared_lock : 생성자에서 lock_shared(), 소멸자에서 unlock_shared()

std::shared_mutex m; 
int share_data = 0;

void Writer()
{
    while (1)
    {
		{
			// std::lock_guard : 생성자에서 lock(), 소멸자에서 unlock()
			std::lock_guard<std::shared_mutex> g(m);
			// m.lock();				
			share_data = share_data + 1;
			std::cout << "Writer : " << share_data << std::endl;
			std::this_thread::sleep_for(1s);			
			// m.unlock();
		}

        std::this_thread::sleep_for(10ms);
    }
}



void Reader(std::string_view name)
{
    while (1)
    {
		{
			std::shared_lock<std::shared_mutex> g(m);	
								// 생성자에서 lock_shared(), 소멸자에서 unlock_shared()
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

    std::jthread t1(Writer);
    std::jthread t2(Reader, "A");
	std::jthread t3(Reader, "B");
	std::jthread t4(Reader, "C");
}



