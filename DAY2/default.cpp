// default.cpp

// trivial
// => 생성자, 복사생성자, 대입연산자 등이 널리 알려진 기본 동작으로 동작하는 것
// => 사용자가 직접 만들면 trivial 하지 않다.

class Point 
{
	int x;
	int y;
public:
	Point(int a, int b) : x(a), y(b) {}
};

int main()
{
	Point p1(1, 2);  // ok
	Point p2; 		 // error. p2도 되게 하고 싶다
}