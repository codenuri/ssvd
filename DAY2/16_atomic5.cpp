#include <iostream>
#include <atomic>

struct Point
{
    int x, y;
    Point() = default;

//  Point(const Point& ) {}	// 이 코드가 있으면 std::atomic<> 에 넣을수 없습니다.
    Point(const Point&) = default;	// 복사 생성자를 컴파일러가 만들어 달라
									// 실제 만드는 것은 아니고 그냥 기본 복사 생성자사용
									// 디폴트 버전의 복사 생성자는 "그냥 메모리 복사"
									// 따라서 atomic 하게 lock-free 로도 수행가능
};

// std::atomic<T> 에서 T의 조건
// => 복사 생성자가 "trivial" 해야 한다.
// => 즉, 사용자가 만든 복사 생성자가 있으면 안된다.
std::atomic<Point> pt; 

int main()
{
    Point ret = pt.load();
}

