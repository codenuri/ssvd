#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;


int share_data = 0; // 파일등의 공유 자원이라고 가정.
std::mutex m;       // 공유 자원 동기화를 위한 뮤텍스

/*
void foo()
{
	m.lock();	// mutex 를 획득하지 못한 스레드는 대기
    share_data = 100; // 공유 자원 사용
	m.unlock();
}
*/
void foo()
{
	// 아래 코드는
	// 1. mutex 획득시 "true" 반환
	// 2. mutex 획득실패시 대기 하지 않고, false 반환
	if ( m.try_lock() )
	{
 	   	share_data = 100; // 공유 자원 사용
		m.unlock();
	}
	else 
	{
		std::cout << "mutex 획득 실패\n";
		// 다른 작업을 하다가 다시 한번 시도해 보면 됩니다.
	}

}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);

    t1.join();
    t2.join();
}



