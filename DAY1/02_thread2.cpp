#include <iostream>
#include <string>
#include <thread>

// 교재 22 page ~ 
// 핵심 : 스레드 함수에 인자를 전달하는 방법 
void f1() { }
void f2(int a, double d) { }
void f3(int a, int& b, std::string&& s) { b = 100; }

// std::string&& : C++11 의 std::move 관련 기술 - 별도의 학습이 필요합니다.
// => 잘 모르시는 분은 그냥 reference 로 이해 하고 수업 들어셔도 됩니다.
// => 정확한 명칭은 "rvalue reference" 입니다.
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

	t1.join();
	t2.join();
	t3.join();

}
// 본과정 복습을 위해서 "동영상강의"가 제공됩니다.
// => 수강을 희망하시면 "ID" 한개만 만들어서 운영자에게 알려주세요
// => 개인 정보와 관련 없는 ID 로 해주세요.





