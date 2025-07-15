#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;

// 핵심 : 아래와 같이 "플래그 변수 + std::condition_variable" 이 전형적인 코딩 관례 입니다.
// => 아래 코드를 완벽히 이해 하세요
// => cv.wait(ul, 함수) 의 로직을 정확히 이해해야 합니다.(주석)

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
	
//	cv.wait(ul);		// 1. ul.unlock()
						// 2. 대기
						// 3. ul.lock() 후에 
						// 4. 다음문장 실행

//	cv.wait(ul, 함수);	// while( !함수()) 
// 						// 		1. ul.unlock()
						// 		2. 대기 - 이곳에서 중단..(CPU 를 사용하지않은 스레드 대기 목록에서)
						//				따라서 busy waiting 은 아닙니다.
						// 		3. ul.lock() 후에 
						// 4. 다음문장 실행

	
	cv.wait(ul, [](){ return data_ready;} );	// 1. data_ready 가 true 이면 대기 없이 다음문장 실행
												// 2. 신호가 와도 data_ready 가 true 가 아니면
												//    다시 대기 

	std::cout << "consume : " << shared_data << std::endl;
}	


void producer()
{
	{
		std::lock_guard<std::mutex> lg(m);
		shared_data = 100;
		std::cout << "produce : " << shared_data << std::endl;

		data_ready = true; // 데이타가 준비 되었다고 표시해 놓고.
							// 이 변수도 공유자원이므로 lock 영역에서 수행
	}
	cv.notify_one(); // 신호 전달
					 // 신호를 받는 소비자가 없어도, data_ready 에 설정했으므로
					 // 소비자는 늦게 도착해도 data_ready 를 통해서 확인 가능
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}