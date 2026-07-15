#include <mutex>

std::mutex m;

int main()
{
	// lock_guard 를 사용하는 2가지 방법
	// 1. 생성자에서 lock 획득
	{
		std::lock_guard<std::mutex> lg(m); // lg 의 생성자에서 m.lock() 수행
		
		// 공유 자원 사용
	}	// <= lg 파괴, 소멸자에서 m.unlock()



	// 2. 이미 lock 획득한 상태의 뮤텍스 관리
	if (m.try_lock())	// m 을 직접 사용해서 lock() 획득
	{					// 그런데, 안전성을 위해 unlock() 은 자동으로 되게 하고 싶다

//		std::lock_guard<std::mutex> lg(m); // error. 생성자가 다시 m.lock() 수행
		std::lock_guard<std::mutex> lg(m, std::adopt_lock); // ok. 생성자에서 m.lock()하지말라
															// => 이미 lock 이 되어 있다는 의미

		// ...
	}   // <= m.unock()
	
}



