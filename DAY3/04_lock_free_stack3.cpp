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

// pop 추가
template<typename T>
class lock_free_stack
{
public:
    std::atomic<node<T>*> head = nullptr;
public:
    void push(const T& data)
    {
        node<T>* new_node = new node<T>(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node));
    }

    T pop()
    {
        while (1)
        {
            node<T>* ret_ptr = head;

            if (ret_ptr == nullptr)
                return 0;

            node<T>* next_ptr = ret_ptr->next;

			// CAS 연산으로 작성한 pop
 		    if (head.compare_exchange_weak(ret_ptr, next_ptr))
            {
                int temp = ret_ptr->data;
                delete ret_ptr;
                return temp;
            }
            // compare_exchange_weak 가 실패한 경우는 처음 부터 다시 작업해야 합니다.
        }
    }
};
lock_free_stack<int> s;


int main()
{
    s.push(10);
    s.push(20);
    s.push(30);

}
