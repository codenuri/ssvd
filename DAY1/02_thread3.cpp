#include <iostream>
#include <thread>

// 핵심 : 스레드 함수의 모양
// => 호출 가능한 모든 것을 사용가능.

void foo(int a, double d) {}		// 일반 함수

struct Machine
{
    void Run(int a, double d) {}	// 멤버 함수
};

// () 연산자를 재정의한 함수 객체
// Work w;
// w(1, 3.4); // w.operator()(1, 3.4)
struct Work
{
    void operator()(int a, double b) const {}
};

// 함수 객체인데, 생성자 인자가 있는 경우.
struct FUNC
{
    int& value;
    FUNC(int& r) : value(r) {}

    void operator()() const
    {
        value = 10;
    }
};

int main()
{
	// #1. 일반 함수를 스레드로
	std::thread t1(foo, 1, 3.4);  // &foo, foo 모두 가능
								  // => 함수 이름은 함수 주소로 암시적 변환 가능

	// #2. 멤버 함수를 스레드로
	// => 객체를 같이 전달해야 합니다.
	// => 반드시 주소 연산자 &를 사용해야 합니다. => 멤버 함수이름은 주소로 암시적 변환 될수 없습니다
	Machine m;
	std::thread t2(&Machine::Run, &m, 1, 3.4); // m.Run(1, 3.4) 를 스레드 수행해 달라. 

	// #3. 함수 객체
	Work w;
	w(1,3.4); // 객체 지만 함수 처럼 사용가능
	std::thread t3(w, 1, 3.4); // ok
//	std::thread t3(&w, 1, 3.4); // error. w() 는 되지만 &w() 는 안됩니다.
								// 함수 주소는 ()로 호출 되지만
								// 객체 주소는 ()로 호출 안됨. 

	// #4. 람다 표현식도 스레드로 수행가능. - 아주 널리 사용
	// => 오늘 오후 부터 계속 사용
	std::thread t4( [](){std::cout << "lambda\n";} ); 

	t1.join();
	t2.join();
	t3.join();
	t4.join();

}

