// 정리
// C++ Concurrency 에서 반드시 알아야 하는 것들

// 1. 스레드를 생성/관리하는 기술
// => std::thread
// => std::jthread
// => std::vector<> 를 가지고 여러개 스레드 관리 기술
// => std::thread(jthread) 는 copy 될수 없지만 move 될수 있다.
// => 최적의 스레드 개수를 결정하는 것이 핵심
//    (HW 상황 고려, 데이터 개수 고려)
// => thread9-3.cpp 예제가 핵심

// 2. 고수준의(high-level) 스레드 동기화 => 비교적 쉬운 내용
// => 내부 구현을 저수준의 기술사용

// 3. 저수준의(low-level) 스레드 동기화 => 어렵고 복잡
// 4. atomic, lock-free
// 5. parallel vs concurrency
// 6. async/coroutine - 스레드는 아니지만 concurrency

