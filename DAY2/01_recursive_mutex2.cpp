#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

class Machine
{
	std::mutex m;
    int shared_data = 0;
public:
    void f1()
    {
		m.lock();
        shared_data = 100;
		m.unlock();
    }
    void f2()
    {
		m.lock();
        shared_data = 100;
		m.unlock();
    }
};

Machine m; // 전역변수(객체), 모든 스레드가 공유

int main()
{
    std::thread t1(&Machine::f1, &m);
    std::thread t2(&Machine::f2, &m);
    t1.join();
    t2.join();
}



