#include <queue>
#include <mutex>
#include <atomic>

std::queue<int> Q;

int x = 0;
int y = 0;

// 아래 함수를 여러개 스레드가 실행한다고 생각해 봅시다..
void foo()
{
	Q.push(20);

	x = 100;
	y = 200;
}

int main()
{

}