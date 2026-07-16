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

	void start( ) 
	{ 
		// 현재 객체의 참조계수를 증가할수 있는 스마트 포인터 생성
		std::shared_ptr<Machine> sp(this); // 가능 할까 ?
									// this 는 raw pointer
									// main 에서 만든 sp 와는 아무 관계가 없다
									// 별도의 Control Block 생성..
									// 이코드는 잘못된 코드
									// [목표] 
									// => 멤버 함수 안에서 스마트 포인터를 만드는 데..
									// => main 의 sp 와 Control Block 을 공유해야 한다.

		std::thread t(&Machine::do_work, this, std::move(sp) ); 
		t.detach();
	}



	void do_work( std::shared_ptr<Machine> self )
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

