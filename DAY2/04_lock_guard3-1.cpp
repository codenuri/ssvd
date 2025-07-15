#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

// lock_guard 에 lock() 을 하지 않는 생성자 만들기

// 방법 #1. bool 변수를 사용해서 if 문 으로
// 단점 
// 1. if 문을 실행해야 하므로 성능 저하
// 2. 가독성 문제 - 아래 A 부분 참고
// 3. 잘못 사용하기 쉽다. - 아래 B 부분 참고

template<typename T>
class lock_guard 
{
	T& m;
public:
	lock_guard(T& m, bool lock_flag = false ) : m(m) 
	{ 
		if ( lock_flag == false )
			m.lock(); 
	} 
	~lock_guard() { m.unlock(); }        
}

void goo()
{
	if ( m.try_lock() )
	{
//		lock_guard<std::mutex> g(m, true); //  A. 가독성 문제, true 의 의미가 불분명하다.
		lock_guard<std::mutex> g(m, 1);    //  B. 이 코드가 에러가 아니다.

	}
}



int main()
{
    std::thread t1(goo);
    
    t1.join();
    
}



