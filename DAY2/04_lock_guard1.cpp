#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

// 핵심 : lock management - RAII 기술
// => 자원의 반납을 함수 마지막 부분에서 하는 것은 아주 나쁜 코드 이다.
// => 함수 중간에서 예외 등의 작업이 발생하면 함수 끝에 도달하지 않을수 있습니다.

// 해결책 
// => 자원의 할당과 해지는 "생성자/소멸자" 를 사용해야 한다.
// => "RAII" - Resource Acquision Is Inintialization
//             자원 할당은 (자원관리 객체)가 초기화 될때 이다.
// 테플릿으로 만든 이유는 "6개 뮤텍스"를 모두 지원하려고.. 
template<typename T>
class lock_guard 
{
	T& m;
public:
	lock_guard(T& m) : m(m) { m.lock(); } // 생성자에서 lock
	~lock_guard() { m.unlock(); }         // 소멸자에서 unlock
}

// 좋은 코드
void goo()
{
    lock_guard<std::mutex> g(m);	// 1. g 의 생성자에서 "m.lock()" 수행
									// 2. g 의 소멸자에서 "m.unlock()" 수행
									// 3. 

	std::cout << "using shared data" << std::endl;

//	throw std::exception(); // 이순간 catch 로 이동
							// => 지역변수는 안전하게 파괴 됩니다.(소멸자 호출)
							// => 따라서 "m.unlock()" 을 하고, catch 로 이동
//	if( ...) return;		// 이런 코드가 있어도 "m.unlock()" 은 보장						
    
}

/*
// 나쁜 코드
void goo()
{
    m.lock();        
	std::cout << "using shared data" << std::endl;
	throw std::exception(); // 예외 발생 - 이런 코드가 있으면 아래 자원해지가 실행되지 못합니다.
    m.unlock();	// 나쁜 코드!!!
}
*/

void foo()
{
    goo();
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    t1.join();
    t2.join();
}



