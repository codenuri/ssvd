#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// Promise & future 모델 : 스레드로 부터 결과값(과 예외)를 꺼내오기 위한 C++의 표준 방법

void add(int a, int b, std::promise<int>& pro )
{
	int s = a + b;

	std::this_thread::sleep_for(3s);

	// 연산의 결과가 나오면 즉시 promise 객체를 통해서 알려 줍니다.
	pro.set_value(s);

	// 이제 남아 있는 마무리 작업 수행..
	// 결과는 이미 위 코드를 통해서 전달 되었음. 
	std::this_thread::sleep_for(2s);
	std::cout << "finish add\n";
}

int main()
{
	// #1. promise 객체를 만들고, 결과를 대기할 future 객체를 꺼내 놓습니다.
	std::promise<int> pro;
	std::future<int> ft = pro.get_future();

	// #2. promise 객체를 참조나 move 로 전달합니다.
	std::thread t(add, 10, 20, std::ref(pro));

	// #3. 주스레드는 다른 작업을 수행하다가...
	std::cout << "주스레드(main) 은 계속 실행\n";

	// #4. 결과가 필요할때 future 객체(ft) 를 통해서 결과를 대기 합니다.
	int ret = ft.get(); // 1. 결과가 있다면 즉시 꺼내고
						// 2. 결과가 없다면 대기 상태에 진입

	std::cout << "결과 : " << ret << std::endl;


	t.join();

	std::cout << "finish main\n";
}



