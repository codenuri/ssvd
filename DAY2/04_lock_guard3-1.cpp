#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

// lock_guard 에 lock() 을 하지 않는 생성자 만들기

// 방법 #1. bool 변수를 사용해서 if 문 으로
template<typename T>
class lock_guard 
{
	T& m;
public:
	lock_guard(T& m, bool lock_flag = false ) : m(m) 
	{ 
		if ( lock_flag == false )
			m.lock(); 
	} 
	~lock_guard() { m.unlock(); }        
}

void goo()
{
	if ( m.try_lock() )
	{
		lock_guard<std::mutex> g(m);
	}
}



int main()
{
    std::thread t1(goo);
    
    t1.join();
    
}



