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
//		auto self = shared_from_this();  

		// 아래 코드가 
		// "동적 할당된 객체의 멤버 함수를 스레드로 수행 할때"
		// "객체가 외부 스마트 포인터에 의해 파괴되는 문제를 해결하기 위한 코드"
		// "아주 전형적인 널리알려진 코딩 패턴 입니다."
		std::thread t( [this, self = shared_from_this() ]() { do_work(); } ); 

		t.detach();
	}

	void do_work( )
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

