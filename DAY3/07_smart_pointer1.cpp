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
	// 1. raw pointer 를 사용하면, 메모리 할당후, 반드시 사용자가 직접 delete 해야 합니다.
	// => 자원을 직접 관리하는 것은 항상 위험 합니다
	// => 그래서 "RAII" 를 사용해야 합니다 - 생성자/소멸자로 자원 관리
	Machine* m = new Machine;
	m->start();
	// <----- 이 위치에서  예외가 발생하면
	delete m;

	// 2. 스마트 포인터 사용시
	// => sp 파괴 될때 소멸자에서 delete 수행
	// => 중간코드에서 예외 나와도 sp 는 안전하게 파괴. 자원 누수 없음. 
	std::shared_ptr<Machine> sp(new Machine);

	// 이제 sp 는 raw pointer 처럼 사용가능
	sp->start();

	// 장점은 사용자가 delete 할 필요 없음

}