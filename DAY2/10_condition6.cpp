#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

std::mutex m;
int shared_data = -1;

// 최종 정리
// #1. std::condition_variable 과 상태 변수를 전역변수로 생성
std::condition_variable cv;
bool ready_data = false;


void consumer()
{
	// #2. 신호 대기시
	// => std::unique_lock 으로 뮤텍스 획득후
	// => cv.wait(ul, prediciate)  : !prediciate 인 경우만 대기 시작
	{
		std::unique_lock<std::mutex> ul(m); 
		cv.wait(ul, [](){ return ready_data == true; } ); 
		std::cout << "consume : " << shared_data << std::endl;
	}
}

void producer()
{
	// #3. 신호를 전달(발생)
	// => std::unique_lock 을 사용할 필요 없음. cv.wait() 에서만 필요. 일반적으로 std::lock_guard 사용
	// => notify_one() 또는 notify_all() 로 신호 발생 
	//    mutex 의 lock 잡고해도 되고 풀고 해도 되지만, 보통은 unlock 후
	{
		std::lock_guard<std::mutex> lg(m);
		shared_data = 100;
		std::cout << "produce : " << shared_data << std::endl;
		ready_data = true;	// 반드시 이 위치
		// cv.notify_one(); // 여기서 해도 되고 unlock()후도 가능.. 
	}
	cv.notify_one(); // 보통은 unlock()후 에..
}



int main()
{
    std::jthread t1(producer);
    std::jthread t2(consumer);
}
