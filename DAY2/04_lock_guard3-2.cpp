#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

// 방법 #2. C++ 표준에서 사용하는 방법
// => std::lock_guard 클래스 외에 다른 수많은 표준에서 사용하는 기술

// #1. empty class 를 설계 합니다.
// => 어떠한 멤버도 없지만, 하나의 독립적인 타입 입니다
class adopt_lock_t {};

// #2. empty class 의 객체를 한개만 전역적으로 생성합니다.
adopt_lock_t adopt_lock;

// #3. 생성자를 2개 만듭니다.
template<typename T>
class lock_guard 
{
	T& m;
public:
	lock_guard(T& m ) : m(m) { m.lock();}
	lock_guard(T& m, adopt_lock_t ) : m(m) { }
	
	~lock_guard() { m.unlock(); }        
}

void goo()
{
	// lock 은 다른 방법(try_lock) 으로 했는데,
	// unlock 직접 하면 안전하지 않다.
	// unlock 만 lock_guard로 하고 싶다.
	
	if ( m.try_lock() )
	{
//		lock_guard<std::mutex> g(m); 			 // 생성자에서 lock 해달라는 의미
		lock_guard<std::mutex> g(m, adopt_lock); // 생성자에서 lock 하지 말라는 의미
												 // => 이미 lock 이 되어 있다(adopt lock)

//		m.unlock(); // 나쁜 코드												 	
	}
}



int main()
{
    std::thread t1(goo);
    
    t1.join();
    
}



