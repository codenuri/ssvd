template<typename T>
class lock_guard 
{
	T& mtx;
public:	
	~lock_guard() 			  { m.unlock();}

	// 목표
	// => lock()을 수행하는 생성자와 수행하지 않지 않은 생성자가 필요 합니다.

	// 구현 방법 #1. bool 타입의 인자 사용 - 예전스타일의 코드 
	// => 단점 #1. 인자의 의미가 명확하지 않다 "g2(m, false)" 에서 false 가 명확하지 않음.
	// => 단점 #2. 성능 저하 (컴파일 시간 문맥을 지원 못함)
	//             if 는 실행시간 결정 
	lock_guard(T& m, bool required_lock = true) : mtx(m) 
	{
		if ( required_lock )
		 	m.lock();
	}
};

// 방법 #1 에 대한 사용자 코드
std::mutex m;
lock_gaurd<std::mutex> g1(m); 		 // m.lock()
lock_gaurd<std::mutex> g2(m, false); // m.lock() 안함 
//-------------------------------------------------------



// 함수 오버로딩에 사용한 타입을 만들기 위해 empty class 기술 사용
class adopt_lock_t {};		// 멤버가 한개도 없지만, 하나의 완전한 타입이므로 인자로 사용 가능
adopt_lock_t adopt_lock;	// 전역변수 한개 생성

template<typename T>
class lock_guard 
{
	T& mtx;
public:	
	~lock_guard() 			  { m.unlock();}

	// 방법 #2. 함수 오버로딩
	// => 장점 1: 인자의 이름이 명확하다.. 가독성이 좋다
	// => 장점 2: 함수 오버로딩에서 어떤 함수를 호출할지 결정은 컴파일 시간. 
	//			 즉, 실행시간 오버헤드가 없다.
	// => 장점 3: 2번째 인자는 함수 내부에서 사용안함. 오직 오버로딩 결정을 위해 사용
	//           최적화되어서 사라지게 됩니다.(인자의 변수이름을 생략하는 것이 좋습니다. 최적화 도움)
	lock_guard(T& m) : mtx(m) { m.lock(); }
	lock_guard(T& m, adopt_lock_t) : mtx(m) { }
};

lock_gaurd<std::mutex> g1(m); // m.lock()
lock_gaurd<std::mutex> g2(m, adopt_lock); // m.lock() 안함