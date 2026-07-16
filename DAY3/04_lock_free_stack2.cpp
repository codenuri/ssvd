#include <atomic>
#include <memory>
#include <iostream>
#include <mutex>

template<typename T> struct node
{
    T data;
    node* next;
    node(T const& data_) : data(data_) {}
};

// 이 코드 핵심
// => 포인터값 비교후 대입 하는 연산을 CPU 자체가 원자 연산으로 제공하면
// => mutex 등이 없어도 스레드 안전 stack 가능합니다

template<typename T>
class lock_free_stack
{
public:
    std::atomic<node<T>*> head = nullptr;
public:
    void push(const T& data)
    {
        node<T>* new_node = new node<T>(data);
        new_node->next = head;

        while (!head.compare_exchange_weak(new_node->next, new_node));

        // head.compare_exchange_weak()는 아래 처럼 동작하는데 
        // lock-free 입니다. (즉, 함수 실행중에 다른 CPU는 head를 접근할수 없습니다.)
        // 
        // if ( head == new_node->next)
        // {
        //    head = new_node;
        //    return true;
        // }
        // else
        // {  
        //      new_node->next = head;
        //      return false;
        // }
            
        // compare_exchange_weak 같은 함수를 "CAS(Compare And Swap)" 이라고 합니다.
        // CPU 가 CAS 명령만 지원 하면 "스택, list" 같은 자료 구조를 mutex 없이 만들수 있다
        // 는 개념이 "lock free 자료구조"입니다.
    }
};

// A.CAS(B, C)

/*
if (A == B)
{
    A = C;
    return true;
}
else
{
    C = A;
    return false;
}
*/


lock_free_stack<int> s;


int main()
{
    s.push(10);
    s.push(20);
    s.push(30);

}
