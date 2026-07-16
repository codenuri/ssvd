#include <atomic>

// 아래 코드의 문제점은 ?
// 1. 전역변수를 2개이상의 스레드가 접근하므로 "동시접근(data race)" 문제 발생
// 2. 

// godbolt.org 사이트에 접속
// 1. 왼쪽 언어 선택 콤보에서 C++ 선택
// 2. 현재 코드 모두 복사해서 왼쪽 편집창에 넣으세요

int a = 0;
int b = 0;

void threadA()
{
    a = b + 1;
    b = 1;
}

// threadB
void threadB()
{
    if (b == 1)
    {
		// a == 1 임을 보장 할수 있을까 ?
		assert( a == 1 );
    }
}

int main()
{
}
