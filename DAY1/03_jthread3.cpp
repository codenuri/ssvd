#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// 새로운 스레드가 "취소" 되도록 하려면
// flag 변수를 사용해야 합니다.

// 아래 코드를 C# 에서 "cooperative cancelation(협력적 취소)" 라고합니다
// 그런데, 아래 코드는
// 스레드가 1개 라서 => main 에서 한개 bool 이면 됩니다.
// 스레드가 10개 라면 => main 에서 10개 bool 변수 필요
// => 결국 스레드당 한개 필요!!
// => jthread 가 이기술을 지원

void foo( bool& quit_signal )
{
	for ( int i = 0; i < 10; i++ )
	{
    	std::cout << "foo : " << i << std::endl;
		std::this_thread::sleep_for(1s);

		if( quit_signal == true )
			break;
	}
	// 스레드가 사용하던 자원등이 있었다면 
	// "마무리 작업" 후에 안전하게 종료
	std::cout << "finish foo\n";
}

int main()
{
	bool quit = false;
    std::thread t1(&foo, std::ref(quit));

	std::this_thread::sleep_for(3s);

	quit = true;  // 스레드에 종료 하라고 신호 전달

	// 스레드가 마지막 작업후 안전하게 종료될때를 대기
    t1.join();
	std::cout << "finish main\n";
}

