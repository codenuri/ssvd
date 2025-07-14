#include <iostream>
#include <thread>
#include <future>

/*
void add(std::promise<int>&& p, int a, int b)
{
	p.set_value(a + b);
}
*/
// 일반 함수 : 함수의 return 을 사용해서 값을 반환
// 하지만 이함수를 "스레드로 수행"해서 결과를 얻으려면 위 처럼 변경해야 합니다.(promise/future)

// 아래 함수를 변경하지 말고 그대로 스레드로 수행해서 결과를 얻으려면 
// 방법 #1. std::packaged_task
// 방법 #2. std::async
int add(int a, int b)
{
	return a + b;
}

int main()
{
	// #1. std::packaged_task 타입의 객체를 생성합니다.
	std::packaged_task<int(int, int)> task(add);

	// #2. std::packaged_task 타입의 객체안에도 future가 있습니다.
	std::future<int> ft = task.get_future();

	// #3. task 를 직접 실행하거나(주스레드), 새로운 스레드로 실행합니다.
	// task(10, 20); // 주스레드가 add 실행

//	std::thread t(std::ref(task), 10, 20); // task 를 계속 사용하려면 이렇게 해도 되는데
    std::thread t(std::move(task), 10, 20); // 보통은 move 사용


	// #4. future 객체로 결과를 얻어서 사용
	int ret = ft.get();

	std::cout << "결과 : " << ret << std::endl;

	t.join();
}



