#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

// std::condition_variable 사용 방법

// #1. 전역변수로 생성
std::condition_variable cv;

void consumer()
{
	// #2. 소비자는 cv.wait()
	// => 1. std::unique_lock() 으로 mutex 획득
	// => 2. cv.wait(ul) <= 이 순간 신호가 올때를 대기

    std::unique_lock<std::mutex> ul(m);
	cv.wait(ul);

    std::cout << "consume : " << shared_data << std::endl;
}

void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;

	// #3. 생산자는 생산후에 cv 를 사용해서 신호 전달
	cv.notify_one(); // 대기중인 한개 스레드만 신호 전달
					 // notify_all() 대기중인 모든 스레드에 전달
}



int main()
{
    std::jthread t1(producer);
    std::jthread t2(consumer);
}