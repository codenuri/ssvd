#include <iostream>
#include <thread>

// 핵심 : 스레드 함수의 모양
// => 모든 callable(()를 사용해서 호출 가능한 모든 것)을 사용가능
// => 함수, 멤버 함수, 람다표현식, 함수 포인터, 함수에 대한 참조, 함수객체(()연산자를 재정의한 클래스)
void foo(int a, double d) {}

struct Machine
{
    void Run(int a, double d) {}
};
struct Work
{
    void operator()(int a, double b) const {}
};

int main()
{
	// #1. 일반 함수
	std::thread t1(foo, 1, 3.4);  // ok
//	std::thread t1(&foo, 1, 3.4); // ok

	// #2. 람다표현식 - 요즘에 아주 널리 사용, 유행하는 코드, 강의에서도 아주 많이 사용
	std::thread t2( []() { }  );


	// #3. 멤버 함수를 스레드로
	// 주의 사항 #1 : 반드시 객체도 전달해야 한다.
	//			   => 단, 스레드가 실행되는 동안 객체(m) 는 파괴 되면 안된다
	//			   => 내일, 스마트 포인터로 안전하게 관리하는 기술 등장
	// 주의 사항 #2 : &Machine::Run 만 가능, & 생략 안됨
	Machine m;
	std::thread t3(&Machine::Run, &m, 1, 3.4); // m.Run(1, 3.4) 를 스레드로 수행해 달라.
//	std::thread t3(Machine::Run, &m, 1, 3.4);  // error

	// "일반 함수 이름" 은 함수주소로 암시적 형변환 가능
	// "멤버 함수 이름" 은 멤버 함수주소로 암시적 형변환 안됌 <== 중요!

	// 멤버 함수를 스레드로 수행시, 람다 표현식이 더 편한경우가 많습니다.
	std::thread t4([&m]() { m.Run(1, 3.4);} );  // 결국 m.Run(1,3.4) 를 스레드로 수행과 동일한 효과

	// #4. 함수 객체
	Work w; // 함수가 아닌 객체지만
	w();    // 이렇게 사용가능, operator() 연산자 제공
			// w.operator()() 의 원리
	std::thread t5(w);	// ok	
//	std::thread t5(&w); // error  w()는 되지만 (&w)() 는 안됨.. 
						// 즉, 함수 객체는 반드시 값 으로 전달

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}

// 람다 표현식 
// => 이름이 없는 함수를 만드는 기술
/*
void f1(int a, double d) {}  // 함수 이름 f1

foo(f1); // foo 에 함수 이름(주소) 전달

// 함수 이름이 전달되는 위치에 함수 이름이 아닌 구현 전달
// => 람다 표현식
// => 만드는 법은 일반 함수와 거의 동일하지만
//    반환 타입과 이름이 없습니다.
//    이름이 없는 함수
foo( [](int a, double d) {} ); 
*/

// 장점 : 인자로 전달시 "일반함수보다 빠른 경우가 있습니다."

// 정확한 원리 : 함수가 아닌 함수 객체를 만드는 표기법



