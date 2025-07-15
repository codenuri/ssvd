#include <iostream>
#include <thread>
#include <atomic>

struct Point { int x, y; }; // 크기 : 8byte(64bit)
							// => 64bit CPU 는 "64bit" 를 atomic 하게 읽고/쓸수 있습니다.

struct Point3D { int x, y, z; };	// 12byte(96byte)
									// => CPU 명령만으로 atomic 하게 할수 없습니다.						 
									// => lock-free 안됨(OS 의 도구 사용)
std::atomic<int> a1 = 0;

std::atomic<Point> a2;  // 사용자 정의 타입도 atomic 에 넣을수 있습니다.

std::atomic<Point3D> a3; 

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
	std::cout << a3.is_lock_free() << std::endl; // g++ 기본은 에러 : 사용하지 말라는 것
											     // g++ -std=c++20 -latomic 로 컴파일시 ok
												 
												 // visual studio : false, 사용가능하지만 lock-free 아님

}

