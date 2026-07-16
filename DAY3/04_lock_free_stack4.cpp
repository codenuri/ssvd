#include <iostream>
#include <thread>
using namespace std::literals;

// lock-free 자료구조의 단점은 
// 결국, push/pop 작업중 다른 스레드가 NODE 를 추가했는지 비교하기 위해 
// "NODE 주소"를 사용한다는 점입니다.

// 300번지, 200번지의 NODE를 삭제 한후..
// 새로운 NODE 를 할당했는데. 우연히 주소가 이전과 같은 주소(300번지)가 나오게 되면
// 버그 입니다.

/*
int main()
{
	int* p = new int;
	printf("%p\n", p);
	delete p;

	p = new int;
	printf("%p\n", p);
	delete p;

	p = new int;
	printf("%p\n", p);
	delete p;

}
*/

void foo()
{
	int* p = new int;
	printf("foo : %p\n", p);
	delete p;

	p = new int;
	printf("foo : %p\n", p);
	delete p;

	p = new int;
	printf("foo : %p\n", p);
	delete p;
}
int main()
{
	std::thread t(foo);

	int* p = new int;
	printf("main : %p\n", p);
	//	delete p;

	p = new int;
	printf("main : %p\n", p);
	delete p;

	p = new int;
	printf("main : %p\n", p);
	delete p;

	t.join();

}

// 결국 새롭게 할당한 NODE의 주소가 방금전에 다른 스레드가 지운 메모리의 주소가 나오면
// 버그로 연결됩니다.
// "ABA Problem" 이라고 불리는 현상입니다.

// 해결책
// 1. Garbage collector 사용
// 2. 항상 다른 메모리 주소가 나올수 있도록 메모리 할당 알고리즘 사용
// 3. NODE 가 필요 없을때 즉시 지우지 말고 약간 지연후 제거

// C++26 에서 위 기술에 대한 해결책을 가진 라이브러리가 추가됩니다.
// ==> "ABA,  Hazard Pointer" 찾아보세요..

// ==> 그래서 C++26 이후에는 lock-free 많이 사용될 확율이 있습니다
// ==> 초창기 (90년대 ~ 2000년) 각광 받았지만, 요즘은 약간 정체.. 