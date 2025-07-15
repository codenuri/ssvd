#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1; // 아직 데이타 없음.

// #1. std::condition_variable 타입의 전역변수 생성
std::condition_variable cv;


void consumer()
{
	// #2. 소비자는 cv.wait()
    std::unique_lock<std::mutex> ul(m);	// lock_guard 가 아닌 unique_lock 사용
	cv.wait(ul);	// 신호 대기

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;

	// 생산자는 생산후에 대기중이 스레드를 깨우기 위해 신호를 전달
	cv.notify_one(); // cv.wait()로 대기중인 스레드중 한개만 깨우기
					 // 모두 깨우려면 cv.nofity_all()
}
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}