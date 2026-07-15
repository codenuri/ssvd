// 02_shared_mutex2  복사
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
#include <condition_variable>
using namespace std::literals;


// 1개의 생성자
// 3개의 소비자 예제

std::shared_mutex m; 
int share_data = 0;

// 생산후에만 소비 가능하도록 condition variable 도입
// std::condition_variable cv;	// std::unique_lock 만 사용가능
								// std::shared_lock(shared_mutex) 기능 사용못함

std::condition_variable_any cv; // 다양한 lock management 와 같이 사용가능(any 의 의미)
								// std::shared_lock 과 연동 가능.
								// 단, 약간의 오버헤드 있다
// 일반적인 관례 
// shared_mutex 기능 필요 : std::condition_variable_any
// 그외                   : std::condition_variable							

bool ready_data = false;

void Writer()
{
    while (1)
    {
		{
			std::lock_guard<std::shared_mutex> g(m);
			share_data = share_data + 1;
			std::cout << "Writer : " << share_data << std::endl;
			std::this_thread::sleep_for(1s);
			
			ready_data = true;
		}
		//cv.notify_one();
		cv.notify_all();

        std::this_thread::sleep_for(10ms);
    }
}
void Reader(std::string_view name)
{
    while (1)
    {
		{
			// std::condition_variable_any 이므로 shared_lock 가능
			std::shared_lock<std::shared_mutex> g(m);
			cv.wait(g, []() { return ready_data; });

			std::cout << "Reader(" << name << ") : " << share_data << std::endl;
			std::this_thread::sleep_for(500ms);	
		}

        std::this_thread::sleep_for(10ms);
    }
}

int main()
{

    std::jthread t1(Writer);
    std::jthread t2(Reader, "A");
	std::jthread t3(Reader, "B");
	std::jthread t4(Reader, "C");
}



