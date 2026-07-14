#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// promise & future 모델
// => 스레드로 수행중인 함수의 결과값을 얻기 위한 C++ 표준 방법
// => 1회 사용만 할수 있습니다.
//    pro.set_value() 는 한번만 호출 가능

// 만일 여러번 해야 한다면
// => 저수준의 동기화 기술(뮤텍스, 조건변수) 등을 사용해서 직접 구현


// #1. 스레드 함수가 인자로 std::promise 를 참조로 받아야 합니다. 
void add(int a, int b, std::promise<int>& pro)
{
	int result = a + b;	

	// #2. 함수 안에서 연산의 결과가 나오면 즉시 promise 를 통해서 알려 줍니다
	pro.set_value(result);

	// 이제 마무리 작업을 하고 스레드는 종료!!
}

int main()
{
	// 스레드 생성 코드

	// #3. std::promise 객체를 만들고 std::future 객체를 꺼냅니다.
	std::promise<int> pro;
	std::future<int> ft = pro.get_future();

	// ft 안에서 int 를 얻을수 있는데, 지금은 아직 값이 없고, 미래에 얻게 됩니다.
	// 그래서 "미래의 결과" 라는 의미로 이름이 future 입니다.

	// #4. 스레드 생성시 std::promise 를 참조로 전달
	std::thread t(add, 10, 20, std::ref(pro));

	// 주스레드는 다른 작업을 하다가...

	// 결과가 필요하면 future(ft) 에서 꺼내면 됩니다.
	int result = ft.get(); 	// 결과가 있으면 즉시 꺼내고, 
							// 없으면 대기(blocking)
						    // => 스레드 종료에 대한 대기가 아니라, 연산의 결과를 대기하는 것

	std::cout << "result: " << result << std::endl;

	t.join(); 	// 스레드 종료 대기 
}



