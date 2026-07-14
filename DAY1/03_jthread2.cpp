#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

// cooperative cancelation(협력적 취소)

void foo( bool& quit_signal )
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

		if ( quit_signal == true )
		{
			std::cout << "receive quit_signal\n";
			break;
		}
    }
	// 스레드가 사용하던 다양한 자원을 정리하고
	// 안전하게 종료
	std::cout << "finish foo\n";
}

int main()
{
	bool quit_signal = false;

    std::thread t(foo, std::ref(quit_signal));
    
    std::this_thread::sleep_for(2s);

	quit_signal = true;  // 스레드에게 종료 요청

	t.join();
}