#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
#include <condition_variable>
using namespace std::literals;

// 생산자 1개, 소비자 3개인 모델

std::shared_mutex m;	
int share_data = 0;

// 생산후에만 꺼내 갈수 있도록
//std::condition_variable cv;	// 반드시 std::unique_lock 과 같이 사용해야 합니다.
							// cv.wait() 시에 lock()/unlock() 사용
							// shared_mutex 의 lock_shared 기능 사용안됩니다.
	
std::condition_variable_any cv; // shared_lock 등도 사용가능.

bool data_ready = false;


void Writer()
{
    while (1)
    {
		{			
			std::lock_guard<std::shared_mutex> g(m);
        	
			share_data = share_data + 1;
			std::cout << "Writer : " << share_data << std::endl;
			std::this_thread::sleep_for(1s);        	

			data_ready = true;
		}
		cv.notify_all(); // 대기중인 모든 스레드를 깨우기. 

        std::this_thread::sleep_for(10ms);
    }
}

void Reader(std::string_view name)
{
    while (1)
    {
		{
			
			std::shared_lock<std::shared_mutex> g(m); 
			cv.wait(g, [](){ return data_ready;} );

			std::cout << "Reader(" << name << ") : " << share_data << std::endl;
			std::this_thread::sleep_for(500ms);
		}
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    std::thread t1(Writer);
    std::thread t2(Reader, "A");
	std::thread t3(Reader, "B");
	std::thread t4(Reader, "C");
    t1.join();
    t2.join();
	t3.join();
	t4.join();
}



