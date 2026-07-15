#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

class Machine
{
//	std::mutex m;
	std::recursive_mutex m;
    int shared_data = 0;	// file 같은 것이라고 생각해 보세요. 
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
		f1();		// 다시 자신의 멤버 함수 호출
        shared_data = 200;
		m.unlock();
    }
};
int main()
{
    Machine m;
    std::jthread t1(&Machine::f1, &m);
    std::jthread t2(&Machine::f2, &m);
 
}



