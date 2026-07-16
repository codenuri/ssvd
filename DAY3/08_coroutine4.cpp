#include <iostream>
#include <coroutine>
#include <utility>

class Task
{
public:

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

    std::coroutine_handle<promise_type> coro; 

    Task(std::coroutine_handle<promise_type> coro) : coro{ coro } {}    

	// 이제 Task 타입 개발자가
	// 사용자들이 사용하기 쉽게 개발해 주면 됩니다
	void continue_run()
	{
		coro.resume();
	}

	~Task() 
	{
		if ( coro.done() )
			coro.destroy();
	}
	int get() 
	{
		return coro.promise().value;
	}
};


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
    co_yield 1;			

    std::cout << "foo #2\n";
    co_yield 2;
    
    std::cout << "foo #3\n";
}  
int main()
{
    Task task = foo();	
	
    task.continue_run();
    std::cout << "main: " << task.get() << '\n'; // 1

    task.continue_run();
    std::cout << "main: " << task.get() << '\n'; // 2

    task.continue_run();	
}

// 이 단계의 핵심
// => 코루틴 규칙 대로 Task 설계후..
// => 사용자들이 편리하게 사용할수 있도록 다양한 기능을 Task 에 추가해 주면됩니다.
// => 위코드는 resume(), 값 얻기, 파괴 등을 편리하게 하는 기본 기능 제공

