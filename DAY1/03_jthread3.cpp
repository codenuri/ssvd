#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// 새로운 스레드가 "취소" 되도록 하려면
// flag 변수를 사용해야 합니다.

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

