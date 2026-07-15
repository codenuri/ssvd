#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std::literals;
std::mutex m;
int shared_data = -1;

std::condition_variable cv;
bool ready_data = false;

// condition_variable 의 사용형태

// cv.wait(ul)            : 가능하지만 거의 사용하지 않음
// cv.wait(ul, predicate) : 대부분의 사용형태
// predicate : bool 을 반환 하는 함수(조건자)


void consumer()
{
    std::this_thread::sleep_for(10ms);

	std::unique_lock<std::mutex> ul(m); 

//	while ( ! ready_data )	
//	{
//		cv.wait(ul);	
//	}

	cv.wait(ul, [](){ return ready_data == true; } ); // 이 코드가 위와 동일!!!
				// cv.wait(ul, predicate )

				// while( !predicate )
				// {	
				//		ul.unlock()
				//		신호 대기
				//		ul.lock()
				// }
				// 이후 코드.. 



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
