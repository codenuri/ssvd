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
	// 아래 작업은 새로운 스레드에 수행됩니다.
	// => 작업중에는 절때 Machine 객체 파괴 되면 안됩니다.
	// => 그런데, Machine 객체의 수명 관리는 "주스레드가 가진 sp" 입니다.
	// => 즉, A 스레드가 사용하는 객체의 수명을 "주(다른) 스레드가 수명 관리" - 너무 위험 합니다.
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

