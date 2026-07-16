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

	// 해결책 
	// => 스레드가 자신만의 스마트 포인터를 가지고 실행
	// => 스레드 종료시 까지 스마트 포인터가 있으므로
	// => 주스레드의 sp 가 파괴되어도 안전

	void start( std::shared_ptr<Machine> sp ) 
	{ 
		std::thread t(&Machine::do_work, this, std::move(sp) ); // this.do_work() 를 스레드로 실행
		t.detach();
	}

	void do_work( std::shared_ptr<Machine> self )
	{	
		// do_work 를 실행하는 동안 main sp 의 복사본을 인자 self 로 받게 되므로
		// 이 함수가 종료 될때 까지 self 는 살아있습니다.
		// 즉, Machine 객체 파괴 안됨. 
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
		sp->start(sp);	
	}	

	getchar(); 
}

