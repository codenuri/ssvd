#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;
// 은행 계좌
struct  Account
{
	std::mutex m;
    int money = 100;
};

// acc1 의 계좌 => acc2 의 계좌로 이체 하는 함수
void transfer(Account& acc1, Account& acc2, int cnt)
{
	
//	std::lock(acc1.m, acc2.m);
	
	// std::lock() : 여러개 mutex 를 동시에 획득하는 함수
	//				 RAII 도구는 아니므로 unlock() 은 직접 해야 합니다.

	// std::scoped_lock : 생성자에서 std::lock() 을 사용하는 RAII 도구
	//					  즉, 여러개 mutex 를 동시에 획득후, 소멸자에서 자동으로 unlock

	std::scoped_lock<std::mutex, std::mutex> g(acc1.m, acc2.m);


    acc1.money -= cnt; 
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

//	acc2.m.unlock();
//	acc1.m.unlock();
}

int main()
{
    Account kim, lee;
    std::jthread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::jthread t2(transfer, std::ref(lee), std::ref(kim), 5);
}

