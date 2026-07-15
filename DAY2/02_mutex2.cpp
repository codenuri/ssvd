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
	if( m.try_lock()) 
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



