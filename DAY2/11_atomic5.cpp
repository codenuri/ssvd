#include <iostream>
#include <atomic>

// 핵심 : std::atomic<TYPE> 에서 TYPE 은
// => 사용자가 만든 복사 생성자가 없어야 합니다.

struct Point
{
    int x, y;
    Point() = default;

    //Point(const Point& ) {}	   // 이코드가 있으면 에러
    Point(const Point&) = default; // 이 코드는 ok
};

std::atomic<Point> pt;

int main()
{
    Point ret = pt.load();
}

