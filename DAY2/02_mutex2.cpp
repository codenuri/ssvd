#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

std::mutex m;	// 공유 자원을 보호하기 위한 mutex
int share_data = 0;

/*
void foo()
{
	m.lock();	// mutex를 획득하지 못한 스레드는 대기 
    share_data = 100;
	m.unlock();
}
*/
void foo()
{
//	m.lock();			// 획득 실패시 대기
	if( m.try_lock()) 	// 획득 실패시 대기 없이 false 반환
	{
    	share_data = 100;
		m.unlock();
	}
	else 
	{
		std::cout << "mutex 획득 실패. 다른 작업을 수행\n";
	}
}

int main()
{
    std::jthread t1(foo);
    std::jthread t2(foo);
}



