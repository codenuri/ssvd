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
// => cv.notify_one() 하는 순간에 소비자는 아직 "cv.wait()" 를 하지 않고 있다
// => 생산자의 신호가 사라진다 ( lost wake 현상 )

// [해결책]
// => 상태 변수를 만들고
// => 대기 전에 상태 변수 조사

bool ready_data = false;

void consumer()
{
    std::this_thread::sleep_for(10ms);

	std::unique_lock<std::mutex> ul(m); 

	if ( ! data_ready )	// 데이터가 준비 되면 대기할 필요 없다
	{
		cv.wait(ul);	
	}
    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
//  std::this_thread::sleep_for(10ms);

    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;

	data_ready = true;
	
	cv.notify_one(); 
}



int main()
{
    std::jthread t1(producer);
    std::jthread t2(consumer);
}