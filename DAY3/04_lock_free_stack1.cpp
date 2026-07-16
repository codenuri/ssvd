#include <atomic>
#include <memory>
#include <iostream>
#include <mutex>

// Single Linked List 에서 사용하는 node 입니다.
template<typename T> struct node
{
    T data;
    node* next;
    node(T const& data_) : data(data_) {}
};

template<typename T>
class thread_safe_stack
{
public:
	std::mutex m;
    node<T>* head = nullptr;
public:
    // 아래 코드가 전형적으로 list 에 앞에 넣는 코드 입니다.
    void push(const T& data)
    {
        node<T>* new_node = new node<T>(data);

		// 멤버 데이터인 head 를 사용하는 코드만 동기화 하면 됩니다
		std::lock_guard<std::mutex> g(m);
        new_node->next = head;
        head = new_node;
    }
};

thread_safe_stack<int> s; // 전역변수 이므로 모든 스레드가 공유 합니다.
						  // 여러스레드에서 동시에 push 사용시 멤버데이터 head 를 동시접근하게 되므로
						  // "thread-safe" 하려면 동기화 필요

int main()
{
	// 이제 위 stack 은 mutex 로 동기화 했으므로
	// 멀티 스레드 환경에서 사용해도 안전합니다
	// "thread-safe class"
    s.push(10);
    s.push(20);
    s.push(30);
}

