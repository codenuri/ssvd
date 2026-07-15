#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

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
	std::jthread t2(Reader, "B");
	std::jthread t2(Reader, "C");
}



