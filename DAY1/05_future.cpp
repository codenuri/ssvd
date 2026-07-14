#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>& p, int a, int b)
{
    std::this_thread::sleep_for(1s); // 복잡한 연산이라서 1초 정도 소요

    p.set_value(a + b);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::ref(pm), 10, 20);

	// 아래 처럼 사용하면
	// => p.set_value() 할때 까지 무한 대기 합니다
	// => 스레드 함수 에 문제가 발생해서  p.set_value() 하지 못하면 무한 루프
    // int n1 = ft.get();

	std::future_status ret = ft.wait_for(2s); // 2초만 대기 

	if ( ret == std::future_status::ready )
	{
		// 스레드가 p.set_value() 한 경우. 데이터는 준비되었음.. 
		// 아래 코드는 절대 대기 안함
		int n = ft.get();
	}
	else if ( ret == std::future_status::timeout )
	{
		// 대기 시간(2s) 지난 경우
		std::cout << "timeout\n";
	}
	else 
	{	
		// 스레드가 아직 실행 안된 경우
		// 즉, promise 에서 future 는 꺼냈지만, 아직 스레드 생성안됨
	}

    t.join();
}



