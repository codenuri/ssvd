#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

// 핵심
// 1. Write 하고 있는 동안에 Read 하면 안됩니다.
// 2. Write 하고 있는 동안에 Write 하면 안됩니다.
// 3. Read  하고 있는 동안에 Write 하면 안됩니다.
// 4. Read  하고 있는 동안에 Read  해도 됩니다.
//		=> 즉, Read 하는 스레드 끼리는 동시 접근 허용해도 됩니다.
//      => 아래 코드는 Read 스레드의 동시접근을 허용하지 않습니다.

// shared_mutex : 중요한 개념

std::mutex m;
int share_data = 0;

// 공유 데이타에 계속 쓰는 작업을 하는 함수
void Writer()
{
    while (1)
    {
        m.lock();
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
        m.unlock();

        std::this_thread::sleep_for(10ms);
    }
}
// 공유 자원을 읽기만 하는 함수. 
void Reader(std::string_view name)
{
    while (1)
    {
        m.lock();
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
        m.unlock();

        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
	// 핵심 : 공유자원에 쓰는 스레드는 1개 
	//		  공유자원을 읽는 스레드는 3개 
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
	std::thread t3(Reader, "B");
	std::thread t4(Reader, "C");
    t1.join();
    t2.join();
	t3.join();
	t4.join();
}



