#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
using namespace std::literals;

class Machine
{
	int data;
public:
	Machine()  { std::cout << "Machine()\n"; }
	~Machine() { std::cout << "~Machine()\n"; }

	void start() 
	{ 
//		do_work(); 
		std::thread t(&Machine::do_work, this); // this.do_work() 를 스레드로 실행
		t.detach();
	}
	void do_work()
	{
		std::cout << "[Machine] start work\n";
		data = 100;
		std::this_thread::sleep_for(3s);
		std::cout << "[Machine] finish work\n";
	}
};
int main()
{
	{
		auto sp = std::make_shared<Machine>();
		sp->start();	
	}	

	getchar(); 
}

