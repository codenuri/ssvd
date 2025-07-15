#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

class Machine
{
//	std::mutex m;
	std::recursive_mutex m;
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

		f1();	// 멤버 함수에서 다른 멤버 함수 호출 - 이런 경우는 많습니다.
				// 그런데, 결국 이때 m.lock() 이 2번 호출되는 결과가 됩니다.
				// 이런 경우에 사용하는 것이 "std::recursive_mutex" 입니다.

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



