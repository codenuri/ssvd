#include <atomic>

// 아래 코드의 문제점은 ?
// 1. 전역변수를 2개이상의 스레드가 접근하므로 "동시접근(data race)" 문제 발생
// 2. "A" 와 "B" 가 순서대로 실행된다는 보장은 없습니다
//  => 성능 향상을 위해 재배치(reordering 될수 있습니다) 

// godbolt.org 사이트에 접속
// 1. 왼쪽 언어 선택 콤보에서 C++ 선택
// 2. 현재 코드 모두 복사해서 왼쪽 편집창에 넣으세요

// 멀티 스레드 환경에서 반드시 고려할점
// 1. 동시 접근(data race)
// 2. 가시성(visiblity) - threadA 가 쓴 데이터를 threadB 가 읽을수 있는가 ?
//						  threadA 가 자신이 실행하는 cache 에만 쓰고 메모리적용안된경우
// 3. 재배치(reordering)


int a = 0;
int b = 0;

void threadA()
{
    a = b + 1;  // A
    b = 1;      // B
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
