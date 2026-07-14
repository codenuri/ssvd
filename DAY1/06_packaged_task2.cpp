#include <iostream>
#include <thread>
#include <future>

int add(int a, int b)
{
	return a + b;	
}

// 위와 같은 스레드를 고려하지 않은 일반 함수를 
// 스레드로 수행하고 결과를 얻는 방법
// 방법 #1. std::packaged_task
// 방법 #2. std::async

int main()
{
	// #1. 일반 함수를 감싼(wrapper) task 를 생성합니다
	std::packaged_task<int(int, int)> task(add);

	// #2. 특징
	// => 일반 함수는 "호출해야" 결과를 얻을수 있지만  int ret = add(10, 20);
	// => task 는 "호출전에" "미래의 결과" 를 얻을수 있습니다.
	std::future<int> ft = task.get_future();

	// #3. 이제 task 를 사용해서 내부의 호출하면 됩니다.
	// => 현재 스레드가 호출해도 되고
	// => 새로운 스레드로 해도 됩니다.
//	task(10, 20);	// 현재 스레드가 그냥 호출(멀티스레드 아님)


	std::jthread t(std::ref(task), 10, 20);		// 현재 스레드가 아닌 새로운 스레드로 task 실행
												// [주의] task 는 참조로 전달해야 합니다.


	// #4. 결과는 future 를 통해서 받아야 합니다.
	int ret = ft.get();

	std::cout << "result: " << ret << std::endl;
}

// 멀티 스레드를 사용하는 코드를 작성하는데..
// add 같은 함수를 내가 직접 작성하게 된다.
// => promise/future 를 사용하면 됩니다.
// => [장점] 함수 종료(return) 시점이 아닌 데이터가 준비된 시점(연산완료)에 데이터 전달가능

// 그런데, add 같은 함수를 새롭게 만드는 것이 아니라
// 예전에 만들어둔 것이 있다.
// => 스레드를 고려 하지 않았다면 "return" 을 사용하고 있을것 입니다.
// => 이렇게  "return 값" 형태의 함수의 결과를 다른 스레드간 공유하고 싶을때
//    std::packaged_task 사용

// std::packaged_task
// => 반드시 스레드에서만 사용하는 것은 아니고
// => "함수등을 감싼 작업"을 생성하는것
// => [특징] 결과를 담은 변수(future)를 미리 생성가능

// promise, future, task 등의 개념은
// => C++에만 있는 것이 아닙니다.
// => C#, Rust, Python ... 등에도 있습니다..
// => 개념도 유사... 한가지 언어에서 명확히 알면.. 다른 언어는 쉽게 접근 가능. 

