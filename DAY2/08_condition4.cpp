#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1; 

// #1. condition_variable 은 flag 변수와 같이 사용하는 것이 관례 입니다.
std::condition_variable cv;
bool data_ready = false;

void consumer()
{
	std::this_thread::sleep_for(10ms); 
	
    std::unique_lock<std::mutex> ul(m);	

	// #2. cv.wait(ul, 함수) 가 일반 적인 코딩 관례 입니다.
	
//	cv.wait(ul);	
//	cv.wait(ul, 함수);	

	cv.wait(ul, [](){ return !data_ready;});	

	std::cout << "consume : " << shared_data << std::endl;
}	




void producer()
{
	{
		std::lock_guard<std::mutex> lg(m);
		shared_data = 100;
		std::cout << "produce : " << shared_data << std::endl;
	}
	cv.notify_one(); // 이순간 대기하는 스레드가 없습니다.
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}