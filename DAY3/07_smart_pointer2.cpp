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
	std::shared_ptr<Machine> sp1(new Machine);
	std::shared_ptr<Machine> sp2 = sp1;

	// #1. std::shared_ptr 은 보통 raw pointer 2개로 구현
	std::cout << sizeof(sp1) << '\n'; // sizeof(pointer*) * 2 정도. 다를수 있다. 

	// #2. control block 내의 참조계수 출력
	std::cout << sp1.use_count() << '\n';

	


}