#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

//std::mutex m; 	// lock(), unlock() 만 제공

std::shared_mutex m;	// lock(), unlock(),
						// lock_shared(), unlock_shared()

// m.lock() 하면    : 다른 스레드의 lock(), lock_shared() 모두 대기
// m.lock_shared() : 다른 스레드의 lock() 은 대기, lock_shared() 는 대기 안함. 

int share_data = 0;

void Writer()
{
    while (1)
    {
		// 쓰는 동안은 다른 스레드의 Write, Read 모두 금지
		// => 즉, 독점 필요
		// => m.lock()
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();

        std::this_thread::sleep_for(10ms);
    }
}

void Reader(std::string_view name)
{
    while (1)
    {
		// Read 하는 동안에, Write 스레드는 금지 하지만 Read 스레드는 허용
		// => 읽기는 공유
		// => m.lock_shared()
        m.lock_shared();
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
        m.unlock_shared();

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



