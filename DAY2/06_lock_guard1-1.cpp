#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// RAII 기술
// => 자원의 관리는 생성자/소멸자 을 통해서 관리되어야 한다.

template<typename T>
class lock_guard 
{
	T& mtx;
public:	
	lock_guard(T& m) : mtx(m) { m.lock();}
	~lock_guard() 			  { m.unlock();}
};

std::mutex m;

void goo()
{
	lock_guard<std::mutex> g(m);  // 좋은 코드 

//  m.lock();    
    std::cout << "using shared data" << std::endl;

	throw std::exception();

//	m.unlock();
}

void foo()
{
    goo();
}

int main()
{
    std::jthread t1(foo);
    std::jthread t2(foo);
}



