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
//	std::shared_ptr<Machine> sp2(m); // runtime - error. 
									 // => sp1 의 control block 과는 별도의
									 //    새로운 control block 생성
									 // => sp1, sp2 가 다른 control block 사용하므로 버그

	std::shared_ptr<Machine> sp2(sp1); // ok
									   // sp1 의 control block 을 공유

	// 문제를 발생시킨 근본원인은 코드안에
	// => raw pointer "m" 이 있다는 것

	// 처음부터 아래 처럼했어야 한다
	auto sp3 = std::make_shared<Machine>();
	
}

