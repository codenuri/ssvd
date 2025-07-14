#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// 스레드 ID

void foo()
{
    std::cout << std::this_thread::get_id() << std::endl;
}
int main()
{
    std::thread t(&foo);
    
    std::this_thread::sleep_for(1s);

	std::thread::id tid1 = std::this_thread::get_id();
    std::thread::id tid2 = t.get_id();
    
    std::cout << "created thread id : " << tid << std::endl;

    t.join();
}

