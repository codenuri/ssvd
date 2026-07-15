#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

// 핵심

// 1. Write 하는 동안 다른 스레드가 Read  하면 안됩니다.
// 2. Write 하는 동안 다른 스레드가 Write 하면 안됩니다.
// 3. Read  하는 동안 다른 스레드가 Write 하면 안됩니다.
// 4. Read  하는 동안 다른 스레드가 Read  해도 됩니다. <==== 이 부분이 핵심

// 그런데, 아래 코드는 Read 하는 동안에도 다른 스레드는 Read 못하고 대기!!!
// => shared_mutex 로 해결

std::mutex m;
int share_data = 0;

void Writer()
{
    while (1)
    {
        m.lock();
		//----------------------------------
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
		//----------------------------------
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}
void Reader(std::string_view name)
{
    while (1)
    {
        m.lock();
		//-----------------------------------
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
		//-----------------------------------
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
	// 핵심 
	// Write  thread 는 1개!
	// Reader thread 는 3개!
    std::jthread t1(Writer);
    std::jthread t2(Reader, "A");
	std::jthread t3(Reader, "B");
	std::jthread t4(Reader, "C");
}



