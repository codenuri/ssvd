#include <iostream>
#include <coroutine>
#include <utility>
// 1. 클래스 이름 자체는 자유롭게.. Task 아니라도 됩니다.
class Task
{
public:
	// 2. 반드시 내포 타입으로 promise_type 이 있어야 하고
	//    => promise_type 은 반드시 아래 멤버 함수가 있어야 합니다(규칙)
    struct promise_type
    {
        int value = 0;

        std::suspend_always yield_value(int v)
        {
            value = v;
            return {};
        }

        Task get_return_object() { return Task{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend()   noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

	// 3. Task 타입 자체는 "코루틴핸들" 이라는 것을 보관하기 위한 멤버데이터 있어야 합니다.
    std::coroutine_handle<promise_type> coro;   // 멤버 데이터

    Task(std::coroutine_handle<promise_type> coro) : coro{ coro } {}    // 생성자
};

// C++ 로 coroutine 을 만들려면
// 규칙 #1. 함수 안에서 co_await, co_yield, co_return 중에 한개 이상을 사용하면 
//          coroutine 이 됩니다.

// 규칙 #2. 반환 타입은 반드시 "C++언어에서 정한 규칙을 지킨 타입이어야 합니다"
//         => 이부분이 어렵습니다. 규칙이 꽤 많습니다. 위 코드 Task 가 규칙을 지킨 최소 코드

Task foo()
{
	// 핵심 : 코루틴의 앞부분에는 "컴파일러가 추가한 코드가 있습니다"

	// <== 컴파일러가 추가한 코드가 여기 있습니다. ==> 
	// <== 1. 코루틴 수행을 위한 초기화
	// <== 2. 반환 타입인 Task 타입의 객체를 생성해서 반환 
	//        Task 타입안에 coroutine 의 핸들도 보관
	//-----------------------------------------------------
	// 여기서 부터 사용자 코드
    std::cout << "foo #1\n";
    co_yield 1;			// task 객체의 yield_value(1) 을 수행후에
						// main 으로 이동

    std::cout << "foo #2\n";
    co_yield 2;
    
    std::cout << "foo #3\n";
}  
int main()
{
    Task task = foo();	// 이순간 foo() 안에 있는  사용자 코드가 아닌 컴파일러가 생성한 부분이 실행됨
						// 컴파일러 코드에서 Task 객체 생성해서 반환

	// 이제 중단된 코루틴을 재개하려면 핸들이 가진 멤버 함수 resume() 사용
    task.coro.resume();	// foo #1    
    std::cout << "main: " << task.coro.promise().value << '\n'; // 1

    task.coro.resume();	// foo #2
    std::cout << "main: " << task.coro.promise().value << '\n'; // 2

    task.coro.resume();	// foo #3

    if (task.coro.done())
        task.coro.destroy();
}
