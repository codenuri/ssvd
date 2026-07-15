#include <iostream>
#include <thread>
#include <atomic>

struct Point { int x, y; };

std::atomic<int>   a1; // primitive 타입 뿐 아니라
std::atomic<Point> p1; // user defint type 도 atomic 가능

int main()
{
    ++a1; 
    int n = a1.load();

	std::atomic<Point> p2 = p1.load(); // 스레드 safe 하게 load

	// 스레드에 안전하더라도
	// 그 작업이 lock-free(CPU 기능만으로) 인지 ? 아니면 CPU 외에 다른 기능을 사용하는지 ?
	std::cout << a1.is_lock_free() << std::endl;
	std::cout << p1.is_lock_free() << std::endl;
}








