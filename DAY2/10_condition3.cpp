#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;
std::mutex m;
int shared_data = -1;

std::condition_variable cv;

// 이번 코드 핵심 
// => 생산자가 먼저 도착하면 어떻게 될까 ?

void consumer()
{
    std::this_thread::sleep_for(10ms);

	std::unique_lock<std::mutex> ul(m); 
	cv.wait(ul);	
    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
//  std::this_thread::sleep_for(10ms);

    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;

	cv.notify_one(); 
}



int main()
{
    std::jthread t1(producer);
    std::jthread t2(consumer);
}