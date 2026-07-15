template<typename T>
class lock_guard 
{
	T& mtx;
public:	
	~lock_guard() 			  { m.unlock();}

	// 목표
	// => lock()을 수행하는 생성자와 수행하지 않지 않은 생성자가 필요 합니다.

	// 구현 방법 #1. bool 타입의 인자 사용 - 예전스타일의 코드 
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