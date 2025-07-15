#include <iostream>
#include <thread>
#include <atomic>

struct Point { int x, y; };

std::atomic<int> a1 = 0;

std::atomic<Point> a2;  // 사용자 정의 타입도 atomic 에 넣을수 있습니다.

int main()
{
    ++a1; 				// 스레드에 안전하게 1증가
    int n = a1.load();	// 좌변 : a1의 값을 읽을때는 스레드에 안전
						// 우변에 담을때 : n 은 atomic 변수가 아니므로 스레드 안전한 코드는 아니지만
						//				  지역변수이므로 스레드당 한개 입니다.
						//			      결국 이코드는 스레드에 안전 합니다.
	int n2 = a1; // 이렇게 해도 위와 동일					

	Point p2 = a2.load(); // 또는 "Point p2 = a2"	 스레드 안전성은 위와 동일

	// atomic 변수가 lock-free 한가 ?
	// => OS 의 동기화 도구가 아닌 CPU 명령만으로 수행 가능한가?
	std::cout << a1.is_lock_free() << std::endl;
	std::cout << a2.is_lock_free() << std::endl;

}

