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
	void start() { do_work(); }
	void do_work()
	{
		std::cout << "[Machine] start work\n";
		data = 100;
		std::cout << "[Machine] finish work\n";
	}
};
int main()
{
	// 스마트 포인터 사용시
	// => 되도록이면 raw pointer 를 섞어서 사용하지 마세요

	Machine* m = new Machine;
	std::shared_ptr<Machine> sp1(m); // ok 문제 없음
	std::shared_ptr<Machine> sp2(m); // runtime - error. 

	
}

