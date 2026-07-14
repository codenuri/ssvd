#include <iostream>
#include <thread>
#include <chrono>	// 시간 관련 라이브러리
using namespace std::literals;	// 3s, 3ms 등을 사용하기 위해 필요

time_t toUTC(std::tm& timeinfo)
{
#ifdef _WIN32
    std::time_t tt = _mkgmtime(&timeinfo);
#else
    time_t tt = timegm(&timeinfo);
#endif
    return tt;
}

// 연,월, 일, 시, 분, 초 를 인자로 받아서 time_point 객체 반환
std::chrono::system_clock::time_point createDateTime(int year, int month, int day, int hour, int minute, int second)
{
    tm timeinfo1 = tm();
    timeinfo1.tm_year = year - 1900;
    timeinfo1.tm_mon = month - 1;
    timeinfo1.tm_mday = day;
    timeinfo1.tm_hour = hour;
    timeinfo1.tm_min = minute;
    timeinfo1.tm_sec = second;
    tm timeinfo = timeinfo1;
    time_t tt = toUTC(timeinfo);
    return std::chrono::system_clock::from_time_t(tt);
}

int main()
{
	// sleep_for : 현재 스레드를 특정 시간 만큼 재우기
	// => 주의 : 인자로 chrono 타입 사용
  	// std::this_thread::sleep_for(3);	// error

	// #1
	std::chrono::seconds s(3); // 3초 객체
	std::this_thread::sleep_for(s);

	// #2. 임시객체로 전달
	std::this_thread::sleep_for(std::chrono::seconds(3));

	// #3. user define literal 문법 사용
	// 3s 표기법을 잘모르시면 "user define literal" 문법 학습
	std::this_thread::sleep_for(3s); // 3s : std::chrono::seconds(3) 와 동일
	std::this_thread::sleep_for(1min + 30s + 120ms + 12ns);
	// => 강의에서 사용하는 표기법. 알아 두세요

	
	// std::this_thread::sleep_for(시간)   : 시간 동안 재우기
	// std::this_thread::sleep_until(시간) : 시간 까지 재우기
	//			=> chrono 를 정확히 이해 해야 합니다.
	//			=> time_point 라는 타입

	auto tp = createDateTime(2026, 7, 14, 12, 0, 0);
	std::this_thread::sleep_until( tp);	
}




