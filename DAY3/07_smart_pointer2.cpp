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

	// #3. 스마트 포인터를 사용하기로 했다면
	// => 보다 효율적으로 사용하는 것이 좋습니다.

	std::shared_ptr<Machine> sp3(new Machine); // 2번의 동적메모리 할당..
											   // 메모리 파편화 현상 발생

	std::shared_ptr<Machine> sp4 = std::make_shared<Machine>();

	// std::make_shared<T>() 가 하는 일
	// 1. sizeof(T) + sizeof(control_block) 를 한번에 메모리 할당
	// 2. T 와 control block 의 생성자 호출
	// 3. T 와 control block 의 주소를 담은 shared_ptr 반환


	// 요즘은 코딩을 단순화 하기 위해 auto 사용
	auto sp5 = std::make_shared<Machine>();
				// 결국 간단히 정리하면 "new Machine" 하고 주소를 스마트 포인터로 관리하는 코드

	// Machine 에 생성자 인자 보내려면
//	auto sp6 = std::make_shared<Machine>(1, 2); // new Machine(1, 2) 의미
}