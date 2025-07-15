#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// 은행 계정(계좌)
struct  Account
{
	std::mutex m;
    int money = 100;
};

void transfer(Account& acc1, Account& acc2, int cnt)
{
	// 계좌 접근시 mutex 를 획득후 사용합니다.
	
	acc1.m.lock();
	acc2.m.lock();

    acc1.money -= cnt;
    acc2.money += cnt;

	acc1.m.unlock();
	acc2.m.unlock();

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

