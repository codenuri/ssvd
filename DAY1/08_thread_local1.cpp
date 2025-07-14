#include <iostream>
#include <thread>
#include <string>

// 호출시 마다 3의 배수를 차례대로 반환하는 함수를 생각해 봅시다.
// =>
int next3times()
{
//	int n = 0; 	// 지역변수. stack 에 놓이고, 함수 호출이 종료 되면 파괴.
				// 즉, 이렇게 만들면 항상 3 반환
				// 스택은 스레드당 한개씩 생성됩니다.
				// 따라서, 이부분을 2개의 스레드가 수행하면, 각각 자신의 스택에 n 이 생성됩니다.
				// 여러개 스레드가 n 을 사용해도 각각 자신의 n 을 사용
	
//	static int n = 0;	// static 지역변수
						// "static storage(data section)" 에 놓이고, (전역변수 위치와 동일) 
						// 함수 호출이 종료되어도 파괴 안됨.
						// 모든 스레드가 공유, 즉, 프로세스당 한개(프로세스의 자원)
						// 그래서 이함수는
						// "스레드당 작업(3의배수)" 가 아닌 "모든 스레드가 공유하는 3의 배수" 반환

	thread_local int n = 0; // 스레드당 한개의 static storage 공간
							// => 스레드가 각각 따로 생성하는데, 
							// => 함수 호출이 끝나도 파괴되지않은 메모리
							// thread specific storage(TSS, linux) 또는
							// thread local storage(TLS, windows) 라고 부르기도 합니다.
							// 전역변수 앞에도 표기 가능합니다.

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

// 메모리와 스레드
//							소유자								파괴
// stack 				: 스레드 소유, 스레드당 한개		   함수 호출종료시 파괴
// heap  				: 프로세스 소유, 모든 스레드가 공유		free, delete 시 파괴
// data(static_storage) : 프로세스 소유, 모든 스레드 공유	    함수 호출종료되어도 파괴 안됨
// TSS(TLS)			    : 스레드 소유, 스레드당 한개			함수 호출종료되어도 파괴 안됨


// 프로세스가 생성(프로그램이 실행되면)
// 1. 전역변수 공간이 할당되고
// 2. 힙 메모리가 생성됩니다.
// 3. 주스레드가 생성됩니다.
//   => 주스레드의 stack 이 생성되고 (보통 1M, 컴파일/link 옵션에서 크기 변경가능)
//   => 주스레드의 TSS 공간이 할당 됩니다.

// 이제 새로운 스레드 생성시
// 1. 새로운 스레드를 위한 스레드가 스택이 할당 됩니다
// 2. 새로운 스레드를 위한 TSS 공간이 할당됩니다.(크기는 OS 마다 다른데, 
// 											Windows os 는 보통 sizeof(int)*1088 )
//				=> TSS 는 공간 제약이 있으므로 많은 메모리가 스레드 별로 필요하면
//				=> 힙 할당후, 주소만 TSS 에 보관하시면 됩니다.