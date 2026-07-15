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

	// 아래 p2가 되도록 하려면 인자 없는 생성자가 있어야 합니다
	// 방법 #1. 직접 구현을 만들자 - 나쁜 코드 
	// => trivial 하지 않음. 
	Point() {}

	// 방법 #2. 컴파일러에게 구현을 요청하자 - 좋은 코드
	// => trivial 생성자
//	Point() = default;
};

int main()
{
	Point p1(1, 2);  // ok
	Point p2; 		 // error. p2도 되게 하고 싶다
}
// godbolt.org 사이트
// => 다양한 언어의 코드의 컴파일 결과 (기계어) 를 확인 가능한 사이트
