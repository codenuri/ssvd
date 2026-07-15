#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

// 이 예제의 핵심
// #1. std::conditional_variable 을 사용하는 이유
// #2. 기본 코드 순서
// #3. cv.wait(ul)의 정확한 동작 원리
// #4. 생산자가 먼저 도착하면 ??? => 다음예제...

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

    std::unique_lock<std::mutex> ul(m); // mutex 획득

	cv.wait(ul);	// 현재 mutex 는 획득 상태 입니다. cv.wait()가 하는 일은
					// 1. ul.unlock() 을 사용해서 mutex 를 unlock
					// 2. 신호 대기, 즉, mutex 를 놓고서 대기...
					// 3. 신호가 오면 다시 ul.lock() 으로 mutex 획득후 아래 코드 실행

					// => 위 처럼 unlock()을 해야 하므로 std::unique_lock 필요
					// => 왜.. 먼저 mutex lock, wait 하나요 ? 그냥 wait 하면 되지 않나요 ?
					//    마지막 단계에서 설명

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