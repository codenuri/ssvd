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
	// 2개의 뮤텍스를 동시에 획득후 자원에 접근해야 하는 경우가 있다면
	// => 절대 아래 처럼 각각 획득하면 안됩니다.
//	acc1.m.lock();
//	acc2.m.lock();

	// [해결책] 
	// => 한번에 모두 획득하거나.
	// => 실패시 모두 lock 하지 말아야 합니다.
	// => "deadlock" 회피 알고리즘.
	// => std::lock(mutex1, mutex2, mutex3, ... );

	std::lock(acc1.m, acc2.m);
	
    acc1.money -= cnt; 
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

	// 획득은 std::lock() 으로 한번에 하지만 
	// unlock() 은 아래 처럼 각각 하면 됩니다.
	acc2.m.unlock();
	acc1.m.unlock();
}

int main()
{
    Account kim, lee;
    std::jthread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::jthread t2(transfer, std::ref(lee), std::ref(kim), 5);
}

