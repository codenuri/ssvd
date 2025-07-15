#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

// C++ 표준에서 lock/unlock 을 관리하는 도구는 4개 입니다.
// 1. std::lock_guard  : 가장 가볍고, 널리 사용되는 기본 도구
// 2. std::unique_lock : 가장 무겁고, 기능이 아주 많다(멤버 함수가 많음)
// 3. std::shared_lock : shared mutex 전용
// 4. std::scoped_lock : 여러개의 mutex 를 동시에 lock 할때 



std::mutex       m1, m2, m3;
std::timed_mutex tm1, tm2, tm3;

int main()
{
    std::unique_lock<std::mutex> u1;		// 아직, mutex 연결안됨.
    std::unique_lock<std::mutex> u2(m1);    // 생성자에서 lock, 소멸자에서 unlock             	

    std::unique_lock<std::mutex> u3(m2, std::try_to_lock); // 생성자에서 lock 이 아닌 try_lock 해달라
									// std::try_to_lock 도 결국 "전역객체"

    if (u3.owns_lock())
        std::cout << "acquire lock" << std::endl;
    else
        std::cout << "fail to lock" << std::endl;


    m3.lock(); 
    std::unique_lock<std::mutex> u4(m3, std::adopt_lock); // 생성자에서 lock 하지 말라.   


    std::unique_lock<std::timed_mutex> u5(tm1, std::defer_lock);
													// 미래에 lock 을 할예정이다.
													// 이후 u5 에 대해서 lock 호출.
    auto ret = u5.try_lock_for(2s);


    std::unique_lock<std::timed_mutex> u6(tm2, 2s);  // tm2.try_lock_for() 사용
    std::unique_lock<std::timed_mutex> u7(tm3, std::chrono::steady_clock::now() + 2s);
    // tm3.try_lock_until() 사용
}
