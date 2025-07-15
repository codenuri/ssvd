#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1; 

std::condition_variable cv;


void consumer()
{
	// 신호를 대기 하려면(소비자)
	// #1. unique_lock 으로 mutex 를 먼저 lock 해야 합니다.
    std::unique_lock<std::mutex> ul(m);	

	// #2. cv.wait(unique_lock) 호출
	cv.wait(ul);	// 1. ul.unlock() 으로 뮤텍스 lock 을 풀어주고(생산자가 mutex 잡을수 있도록)
					// 2. cv 에 신호가 올때를 대기 합니다. - 여기서 block 상태
					// 3. 신호가 오면 다시 ul.lock()로 lock 획득후 아래 코드 실행
					// => 이처럼 cv 가 내부적으로 명시적으로 lock()/unlock() 호출해야 하므로
					//    std::lock_guard 가 아닌 std::unique_lock 필요

    std::cout << "consume : " << shared_data << std::endl;

}	// <= unique_lock 일 뮤텍스 unlock


void producer()
{
	std::this_thread::sleep_for(10ms);
	{
		std::lock_guard<std::mutex> lg(m);
		shared_data = 100;
		std::cout << "produce : " << shared_data << std::endl;

		// cv.notify_one(); // lock 을 가진 상태로 신호 전달 할수도 있지만
	}
	cv.notify_one(); // // lock 해지후 통보가 효율적입니다.
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}