#include <iostream>
#include <thread>
#include <atomic>

//struct Point { int x, y; };	// 64 bit 크기의 데이타
								// 64 bit CPU 에서는 데이터 처리를 64bit 단위로 수행
								// 64 bit정도의 데이터는 lock-free 로 복사/이동등이 가능

struct Point { int x, y, z; };	// 96 bit.
								// 한개의 명령으로 복사/이동이 되지 않을수 있다. 

std::atomic<int>   a1; // primitive 타입 뿐 아니라
std::atomic<Point> p1; // user defint type 도 atomic 가능

int main()
{
    ++a1; 
    int n = a1.load();

	std::atomic<Point> p2 = p1.load(); // 스레드 safe 하게 load

	// 스레드에 안전하더라도
	// 그 작업이 lock-free(CPU 기능만으로) 인지 ? 아니면 CPU 외에 다른 기능을 사용하는지 ?
	// => Point 크기가 64 보다 크면 mingw 는 A 가 에러지만, C++ 표준에서는 false 반환 입니다.
	std::cout << a1.is_lock_free() << std::endl;
	std::cout << p1.is_lock_free() << std::endl; // A
}








