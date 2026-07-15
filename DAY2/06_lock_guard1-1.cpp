#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// RAII 기술
// => 자원의 관리는 생성자/소멸자 을 통해서 관리되어야 한다.
// => Resource Acquision Is Initialization
//    자원의 획득은 (자원관리 객체가) 초기화 될때이다
//    반납을 중심에 놓은 것이 아니라 획득을 중심에 놓은 용어. 

// C++ 언어 : RAII 를 사용할지 말지는 선택

// Rust 언어 : 모든 자원을 "RAII" 로만 관리된다.!!!
//			  자원 누수를 원칙적으로 방지.!!


template<typename T>
class lock_guard 
{
	T& mtx;
public:	
	lock_guard(T& m) : mtx(m) { m.lock();}
	~lock_guard() 			  { m.unlock();}
};

std::mutex m;
void goo()
{
	lock_guard<std::mutex> g(m);  // 좋은 코드 
								  // 1. lock_guard 의 생성자에서 "m.lock()" 수행
								  // 2. {} 벗어날때 g 파괴. 소멸자 호출. "m.unlock()" 수행
								  // 3. 장점
								  // => 지역변수의 파괴(소멸자 호출) 은 대부분의 경우 안전하게 컴파일러가 보장
								  // => 함수 중간에서 예외가 나와도 "지역변수 파괴는 보장"
								  // => 함수 중간에서 return 해도 "지역변수 파괴는 보장"
								  // => 즉, 항상 m.unlock() 호출 
//  m.lock();    
    std::cout << "using shared data" << std::endl;

//	throw std::exception();
//	m.unlock();
}

void foo()
{
    goo();
}

int main()
{
    std::jthread t1(foo);
    std::jthread t2(foo);
}



