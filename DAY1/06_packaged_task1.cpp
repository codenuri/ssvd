#include <iostream>
#include <thread>
#include <future>

// 일반적인 함수 모양
int add(int a, int b)
{
	return a + b;	// 동일스레드에서만 전달 가능
}
// 위와 같은 함수를 별도의 스레드로 실행하면
// => 반환값을 받기 어렵습니다.

// 그래서 아래와 같이 promise/future 사용
// => 이미 add 가 만들어져 있던 함수라면 아래 처럼 변경하기 어렵습니다.
// => 해결책 : std::pakaged_task, std::async

// add 함수가 promise 를 통해서 반환값 전달
// 다른 스레드에 반환
void add(std::promise<int>& p, int a, int b)
{
	p.set_value(a + b);
}

int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();

	std::thread t(add, std::ref(pm), 10, 20);

	int ret = ft.get();

	t.join();
}



