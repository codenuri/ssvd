#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;
// 아래 코드는 공유자원의 동기화를 위해 mutex
// => 공유 자원의 동시 접근 문제 해결

// 그런데.. 남은 문제는
// => 생산자가 아직 생산을 안했는데..(producer 앞부분에 10ms 지연 있음. 생산에 시간 소요)
// => 소비자가 먼저 소비 하는 경우가 있습니다.

// 생산자가 먼저 생산한 후에 소비되도록 할수 없을까요 ?

// 소비자 : 내가 먼저 도착하면 기다릴테니, 생산을 하면 알려줘!!!
// 생산자 : 생산한후에... 신호줄께..!!

// => std::condition_variable 의 역활!!!


std::mutex m;
int shared_data = -1;

// 소비자 : 공유자원 읽기
void consumer()
{
    std::lock_guard<std::mutex> lg(m);
    std::cout << "consume : " << shared_data << std::endl;
}

// 생산자 : 공유자원에 쓰기
void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;
}



int main()
{
    std::jthread t1(producer);
    std::jthread t2(consumer);
}