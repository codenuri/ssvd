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
// => cv.wait(ul) 가 깨어나도... 실제 데이터가 있다는 보장 없다(가짜 깨움, 다른 소비자가 소비)
// 
// [해결책]
// => ready_data 를 다시 조사!
// => if 대신, while 사용

bool ready_data = false;

void consumer()
{
    std::this_thread::sleep_for(10ms);

	std::unique_lock<std::mutex> ul(m); 

	while ( ! ready_data )	
	{
		cv.wait(ul);	// 1. ul.unlock()
						// 2. 신호 대기
						// 3. ul.lock()	
	}
    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
//  std::this_thread::sleep_for(10ms);

    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;

	ready_data = true;

	cv.notify_one(); 
}



int main()
{
    std::jthread t1(producer);
    std::jthread t2(consumer);
}
