#include <mutex>

std::mutex m;

// 정리

int main()
{
	// lock_guard 를 사용하는 2가지 방법

	// 1. 생성자에서 lock 획득
	{
		std::lock_guard<std::mutex> lg(m);
	}

	// 2. 이미 lock 획득한 상태의 뮤텍스를 자동 unlock 만 관리
	if (m.try_lock())
	{
		std::lock_guard<std::mutex> lg(m, std::adopt_lock);
		
		// std::adopt_lock : 이미 생성되어 있는 전역변수(객체)
		//				     std::adopt_lock_t 라는 empty class 의 객체
	}

	
}



