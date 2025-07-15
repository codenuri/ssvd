#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

struct  Account
{
	std::mutex m;
    int money = 100;
};

void transfer(Account& acc1, Account& acc2, int cnt)
{
	// std::lock() : 여러개 뮤텍스를 안전하게 lock 하는 표준 함수
	//				 단, 이 함수를 직접 사용하면
	//				 각각의 뮤텍스를 직접 unlock() 해야 한다 - 2번 소스
	
	// std::scoped_lock : 생성자에서 여러개의 뮤텍스를 std::lock()으로 안전하게 획득하고
	//					  소멸자에서 unlock()을 지원.

	{
		std::scoped_lock<std::mutex, std::mutex> g(acc1.m, acc2.m);

		acc1.money -= cnt;
		acc2.money += cnt;

	//	acc1.m.unlock();
	//	acc2.m.unlock();
	}
    std::cout << "finish transfer" << std::endl;
}

int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

