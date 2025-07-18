#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// std::this_thread::sleep_for : 현재 스레드를 특정 시간 동안 재우는 함수

time_t toUTC(std::tm& timeinfo)
{
#ifdef _WIN32
    std::time_t tt = _mkgmtime(&timeinfo);
#else
    time_t tt = timegm(&timeinfo);
#endif
    return tt;
}

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
//  std::this_thread::sleep_for(3); // error

	// sleep_for 의 인자는 반드시 chrono 라이브러리 이어야 합니다.
	std::chrono::seconds sec(3);      // 3초를 나타내는 객체 생성후
	std::this_thread::sleep_for(sec); // ok 전달

	// 임시객체로 전달
	std::this_thread::sleep_for( std::chrono::seconds(3)); // ok

	// user define literals 문법 사용
	// => using namespace std::literals 이 필요 합니다.
	std::this_thread::sleep_for(3s); // 3s : std::chrono::seconds(3) 의미의 객체 생성하는 표기법
	std::this_thread::sleep_for(3ms); // 3ns, 3us, 3ms, 3s, 3min, 3h등 모두제공
	//---------------------------------------------------------------------------
	// std::this_thread::sleep_for   : 특정 시간 동안 대기
	// std::this_thread::sleep_until : 특정 시간 까지 대기
	std::this_thread::sleep_until( std::chrono::system_clock::now() + 10s );

	// 특정 시간을 구해서 그때 까지 대기 하기
	// => time_point 구조체 형태로 얻어서 인자로 전달해야 합니다
	auto tp = createDateTime(2025, 7, 14, 12, 0, 0);
	std::this_thread::sleep_until( tp);

	// 이 내용은 "chrono" 표준 라이브러리에 대한 학습이 필요합니다.
}









