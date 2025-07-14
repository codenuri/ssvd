#include <thread>

// 핵심 : std::thread 객체의 copy, move 효과

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
	std::thread t2(&goo);

	// #1. swap 가능합니다.
//	t1.swap(t2); // ok

	// #2. std::thread 객체의 복사와 move 동작
//	std::thread t3 = t1; // error. std::thread 객체는 복사 될수 없습니다.
						 // "복사 생성자가 삭제" 되어 있습니다.
	std::thread t4 = std::move(t1); // ok. std::thread 객체는 move 될수 있습니다.
									// => 중요하고 널리 사용됩니다.
    
	// 이제 t1 을 사용하면 안되고 t4로 사용해야 합니다

	// #3. 스레드 객체를 먼저 만들고 나중에 함수를 연결하는 방법
	std::thread t5;	// 객체만 생성, 아직 스레드는 생성 안됨.

//	t5 = t2; // error. 대입 연산자 필요
	t5 = std::thread(&foo); // 타입이름() : 임시객체를 만드는 표기법
							//             임시객체는 rvalue 이고, 대입연산자가 아닌 move 호출
							// move 대입 연산자 호출



	t2.join();
    t4.join();

}






void f1(std::thread t) 
{
    t.join(); 
}

std::thread f2()
{
    return std::thread(foo());
}
