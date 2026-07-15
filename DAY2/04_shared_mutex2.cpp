#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string_view>
using namespace std::literals;

// 핵심

// 1. Write 하는 동안 다른 스레드가 Read  하면 안됩니다.
// 2. Write 하는 동안 다른 스레드가 Write 하면 안됩니다.
// 3. Read  하는 동안 다른 스레드가 Write 하면 안됩니다.
// 4. Read  하는 동안 다른 스레드가 Read  해도 됩니다. <==== 이 부분이 핵심

// std::mutex m;     // lock(), unlock() 만 제공

std::shared_mutex m; // lock(), unlock() 외에  
					 // lock_shared(), unlock_shared() 추가로 제공
					 // C++17 에서 도입
					 // 흔히 "slim reader" 라는 용어를 사용하기도 합니다.

int share_data = 0;



void Writer()
{
    while (1)
    {
        m.lock();	// 다른 스레드가 획득 할수 없음.
					// 쓰는 동안은 모든 스레드 접근 금지
		//----------------------------------
        share_data = share_data + 1;
        std::cout << "Writer : " << share_data << std::endl;
        std::this_thread::sleep_for(1s);
		//----------------------------------
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}
void Reader(std::string_view name)
{
    while (1)
    {
        m.lock_shared();    // 다른 스레드가  m.lock() 사용하면 대기
							// 다른 스레드가  m.lock_shared() 사용하면 대기 안함..
							// 즉, lock_shared() 끼리는 동기화 안됨
		//-----------------------------------
        std::cout << "Reader(" << name << ") : " << share_data << std::endl;
        std::this_thread::sleep_for(500ms);
		//-----------------------------------
        m.unlock_shared();
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



