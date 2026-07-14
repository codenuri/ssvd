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
	task(10, 20);	// 현재 스레드가 그냥 호출(멀티스레드 아님)

	// #4. 결과는 future 를 통해서 받아야 합니다.
	int ret = ft.get();

	std::cout << "result: " << ret << std::endl;
}



