#include <string>
#include <iostream>

int main()
{
	std::string s1 = "to be or not to be";
	std::string s2 = "to be or not to be";

	std::string s3 = s1;			// 자원(문자열)의 복사
									// => 이 문장 실행후 에도 s1 은 자원(문자열) 소유

	std::string s4 = std::move(s2);	// 자원(문자열)의 이동, 
									// => 이 문장 실행후 s2 는 더이상 자원(문자열) 없음

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
}
