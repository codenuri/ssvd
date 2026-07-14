#include <iostream>
#include <string>
#include <thread>

// 핵심 : 스레드 함수에 인자를 전달하는 방법

void f1() { }
void f2(int a, double d) { }
void f3(int a, int& b, std::string s) { b = 100; }

int main()
{
    int n = 0;
    std::string s = "hello";

    // 인자 전달 방법
	std::thread t1(f1);				// 인자 없는 함수
	std::thread t2(f2, 1, 3.4);		// 인자 있는 함수

	// 핵심reference 와 move 사용
	// std::ref(n) : n 을 참조로 전달해 달라는 의미
	// => 스레드간 참조 전달은 안전하지 않지만 필요한 경우들이 있습니다.
	int n1 = 0;
//	std::thread t3(f3, 1, std::ref(n1), s);				// 3번째 인자를 복사(copy)
	std::thread t3(f3, 1, std::ref(n1), std::move(s));	// 3번째 인자를 이동(move)으로

	t1.join();
	t2.join();
	t3.join();
}

