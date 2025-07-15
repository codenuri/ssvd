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
    lock_guard<std::mutex> g(m);	
}

int main()
{
    std::thread t1(goo);
    
    t1.join();
    
}



