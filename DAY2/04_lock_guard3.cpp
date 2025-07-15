#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

template<typename T>
class lock_guard 
{
	T& m;
public:
	lock_guard(T& m) : m(m) { m.lock(); } 
	~lock_guard() { m.unlock(); }        
}

void goo()
{
//  lock_guard<std::mutex> g(m); // 생성자에서 "m.lock()" 으로 뮤텍스 획득 	

	// m.lock() 말고 m.try_lock() 을 사용하고 싶다
	// => 직접 mutex 멤버 함수 사용해야 합니다.
	if ( m.try_lock() )
	{
		// 이미 획득한 mutex 의 unlock() 만 lock_guard 로 하고 싶다.
		lock_guard<std::mutex> g(m); // m 은 이 lock 을 획득했는데, 이렇게 하면
									 // 다시 lock 이 된다.
									 // 해결책, lock_guard 에 lock() 을 하지 않은 생성자가 있어야 한다.
	}
}



int main()
{
    std::thread t1(goo);
    
    t1.join();
    
}



