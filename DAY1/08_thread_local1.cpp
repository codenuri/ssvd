#include <iostream>
#include <thread>
#include <string>

// 호출시 마다 3의 배수를 차례대로 반환하는 함수를 생각해 봅시다.
// =>
int next3times()
{
//	int n = 0; 	// 지역변수. stack 에 놓이고, 함수 호출이 종료 되면 파괴.
				// 즉, 이렇게 만들면 항상 3 반환
	
	static int n = 0;	// static 지역변수
						// "static storage(data section)" 에 놓이고
						// 함수 호출이 종료되어도 파괴 안됨.

	n = n + 3;
	return n;
}
void foo(const std::string& name)
{
	std::cout << name << " : " << next3times() << std::endl; // 3
	std::cout << name << " : " << next3times() << std::endl; // 6
	std::cout << name << " : " << next3times() << std::endl; // 9
}

int main()
{
//	foo("A");
	
	// foo 를 2개의 스레드가 동시 실행
	std::thread t1(foo, "A");
	std::thread t2(foo, "\tB");

	t1.join();
	t2.join();
}



