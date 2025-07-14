#include <iostream>
#include <string>
#include <thread>

// 교재 22 page ~ 
// 핵심 : 스레드 함수에 인자를 전달하는 방법 
void f1() { }
void f2(int a, double d) { }
void f3(int a, int& b, std::string&& s) { b = 100; }

int main()
{
    int n = 0;
    std::string s = "hello";

    // 인자 전달 방법
	std::thread t1(&f1); // 인자가 없는 함수는 함수 이름(주소)만 전달

	std::thread t2(&f2, 3, 3.4); // 인자가 있다면 thread 생성자로 전달만 하면 됩니다.
	
	// 주의. 
	// #1. 인자가 참조인 경우는 std::ref()로 전달해야 합니다
	// #2. rvalue reference 인 경우는 std::move() 사용
	std::thread t3(&f3, std::ref(n), std::move(s));

	// => 단, 지역변수를 참조로 전달하는 것은 "아주 좋지 않습니다."
	// => 하지만, 필요한 경우가 있습니다. 오후에 등장.. 

}





