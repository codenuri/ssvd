#include <thread>

// 중요한 예제. 반드시 이해해야 합니다. 아주 많이 사용되는 기법들
// copy, move

void f1(std::thread t)   // 인자로 스레드를 받는 함수
{
    t.join(); 
}

std::thread f2()		// 반환 값으로 스레드 반환
{
    return std::thread(foo());
}

void foo() {}
void goo() {}


int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

	// #1. swap 가능
//	t1.swap(t2); 

	// #2. copy, move
//	std::thread t3 = t1;			// error. copy constructor 는 delete 되어 있습니다.
	std::thread t4 = std::move(t1); // ok.    move constructor 는 사용가능.
									// 이후에는 t1은 사용할수 없고, t4를 사용해서 join()
    
	// #3. 대입, 이동 대입
	std::thread t5;	

//	t5 = t2; 				// error. 대입 연산자(assignment operator)도 사용할수 없음
//	t5 = std::move(t2); 	// ok.    move 대입 연산자(move assignment operator)도 사용할수 있음

	t5 = std::thread(&foo); // ok. 우변은 임시객체(temporary)를 생성한것, 임시객체는 rvalue
							//     rvalue 는 copy 가 아닌 move!!
							// 이게 중요한 이유는 "수십개의 스레드를 vector 등에서 관리할때 필요"



	// #4. 함수 인자와 반환 값
	// void f1(std::thread t);

//	f1(t2);					// error. 값으로 전달, copy constructor 가 없음
	f1(std::move(t2));		// ok.    
	f1(std::thread(foo));	// ok.  인자는 temporary, rvalue, move 로 전달

	// #5.  함수가 값으로 반환하면 temporary, rvalue 
	// std::thread f2() { return std::thread(...) }
	auto t6 = f2(); // ok. 우변이 rvalue 이므로 move. 

	t2.join();
    t4.join();
	t5.join();
    t6.join();
}
// move 가 어려우신 분은 위 코드는 몰라도..
// 다음 예제를 이해하면 됩니다.
// => 현재 코드는 다음 예제를 위한 이론
