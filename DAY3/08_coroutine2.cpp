#include <thread>
#include <iostream>
#include <chrono>
using namespace std::literals;

// 동기 함수
void foo(int a, int b) { std::this_thread::sleep_for(3s); }

// 비동기 함수 #1. 내부적으로 스레드 생성
void goo(int a, int b, void(*handler)())
{
	std::thread([handler]() {
		std::this_thread::sleep_for(3s); // 주된 작업
		handler();		// 작업 완료후 사용자가 전달한 핸들러 수행
		}).detach();
}

// 비동기 함수 #2. 내부적으로 OS 제공하는 비동기 함수 사용
void hoo(int a, int b )
{
	// Windows OS 의 WriteFileEx()
	// 대부분 파일, N/W, Serial 등의 등의 HW 관련 I/O 작업
	// Windows 기술 : IOCP
	// Linux   기술 : EPOLL 
	// C++ 표준이 이 부분을 라이브러리로 아직 지원 못함.. 
	// => 다른 언어는 대부분 지원
	// => C++은 C++26의 std::execution 부터 시작..
}


int main()
{
	// #1. 동기 함수 호출
	// => 함수의 모든 코드가 실행 되고 나서 반환
//	foo(1, 2);

	// #2. 비동기 함수 호출
	// => 호출시 함수는 바로 반환 되고
	// => 함수의 주요 기능은 백그라운드로 실행(새로운 스레드 생성 또는 OS 에 요청)
	goo(1, 2, []() { std::cout << "complete async operation\n"; });
	std::cout << "continue main\n";

//	hoo(1, 2);

	// #3. 코루틴 
	//	coroutine(); // 호출시, 함수 일부만 실행되고 반환
	//	coroutine(); // 다시 호출시, 중지되었던 지점 부터 계속 실행

	getchar();
}


void coroutine()
{
	// ...
	// 여기서 호출자(main) 으로 돌아감
	// main 에서 다시 호출시 이후 문장 부터 실행
	// ...
}

// 일반 함수
// main 함수가 시키는 일을 수행
// => "subroutine" 이라는 용어 사용

// 코루틴
// main 함수와 같이 협력(co) 해서 일을 수행
// => "coroutine" 이라는 용어 사용
// => C++20 부터 지원
// => C++ 답게..!! 아주 복잡하고 어려운 스타일로 지원
//    어렵지만 모든 것을 개발자가 직접할수 있는 방식
// => 다른 언어는 정해진 틀에서만 코루틴 지원