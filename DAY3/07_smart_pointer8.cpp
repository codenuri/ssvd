#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
using namespace std::literals;

// std::enable_shared_from_this 클래스 템플릿
// => 멤버 함수 안에서 자신을 가리키는 스마트 포인터를 만드는 데
// => 외부에서 만들어진 스마트 포인터의 Control Block 을 공유

// 멤버 함수를 스레드로 수행하는데, 
// => 스레드가 수행중에는 절대 객체가 파괴 되면 안된다.
// => 객체 파괴를 막기위해 멤버 함수 안에서 스마트 포인터를 생성해서 참조 계수를 증가하는 기술

// #1. 클래스를 std::enable_shared_from_this<자신 클래스이름> 으로 부터 상속
class Machine : public std::enable_shared_from_this<Machine>
{
	int data;
public:
	Machine()  { std::cout << "Machine()\n"; }
	~Machine() { std::cout << "~Machine()\n"; }

	void start( ) 
	{ 
		// #2. 스마트 포인터가 필요할때는 shared_from_this() 함수 사용
		// => std::enable_shared_from_this 에서 상속받는 멤버 함수
		self = shared_from_this();  // 외부에서 만든 스마트 포인터의 control block 을 
									// 공유하는 스마트 포인터 생성
		
		std::thread t(&Machine::do_work, this, std::move(self) ); 
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

