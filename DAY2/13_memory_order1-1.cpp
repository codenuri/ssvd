#include <atomic>

int a = 0;
int b = 0;

void foo()
{
    a = b + 1; 
    
    // 펜스 설치
    // "위 코드는 아래 펜스 아래로 내려갈수 없고"
    // "아래 코드는 펜스위로 올라 갈수 없다."
    // asm("mfence");

    // 아래 C++ 표준이 위 기계어 코드의 역활 입니다.
    // g++ 은 "lock xxx" 기계어로.. 
    std::atomic_thread_fence(std::memory_order_seq_cst);

    b = 1;		
}

void goo()
{
    if (b == 1)
    {
        // a == 1 을 보장할수 있을까 ?
    }
}






