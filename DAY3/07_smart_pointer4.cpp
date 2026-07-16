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
		do_work(); 
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
		sp->start();	// 동기적으로 모든 일을 마치고
	}	// <= Machine 이 파괴되니까.. 안전하다. 

	getchar(); // 종료 방지	
}

