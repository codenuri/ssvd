#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;


// C++ 표준에서 "RAII" 를 사용한 lock 관리 타입은 4개  

// 1. std::lock_guard  : 가장 가벼운 클래스 템플릿, 실제 구현이 06_lock_guard4.cpp 와 거의 동일
// 2. std::unique_lock : 가장 무거운 클래스 템플릿, 기능이 많다. std::condition_variable 에서 사용
// 3. std::scoped_lock : 여러개 뮤텍스를 deadlock 없이 동시에 lock 						
// 4. std::shared_lock : shared_mutex 의 lock_shared 기능을 RAII 로 관리할때

std::mutex       m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
    std::unique_lock<std::mutex> u1;		// 연결된 뮤텍스 아직 없음. 
    std::unique_lock<std::mutex> u2(m1);    // 생성자에서 m1.lock()           	  

    std::unique_lock<std::mutex> u3(m2, std::try_to_lock); // m2.try_lock()
													// lock() 실패시 대기 안함
    if (u3.owns_lock())	// 위에서 시도한 try_lock() 결과 확인
        std::cout << "acquire lock" << std::endl;
    else
        std::cout << "fail to lock" << std::endl;


    m3.lock();	// 명시적 lock() 함수도 제공
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock);   
										// m3 는 이미 lock 되었다. 생성자에서 lock 하지말라

    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
										// 생성자에서 lock 하지말라, 나중에 lock 하겠다
    auto ret = u5.try_lock_for(2s);


    std::unique_lock<std::timed_mutex> u6(tm2, 2s);  // tm2.try_lock_for() 사용
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s);
    // tm3.try_lock_until() 사용
}
