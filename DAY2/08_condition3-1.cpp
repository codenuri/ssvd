#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1; 

std::condition_variable cv;

// 아래 코드의 문제점
// => 소비자가 늦게 실행됩니다. 
// => 생산자가 cv.notify_one() 하는 시점에는 소비자는 cv.wait()하고 있지 않습니다.

// => 뒤늦게 소비자가 cv.wait() 하지만, 신호를 주는 스레드가 없으므로 계속 대기
// 해결책은 다음 예제

void consumer()
{
	std::this_thread::sleep_for(10ms); 

    std::unique_lock<std::mutex> ul(m);	
	cv.wait(ul);	

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