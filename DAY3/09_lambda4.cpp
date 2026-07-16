// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

bool foo(int n) { return n % 3 == 0; }	

struct IsModulus 
{
	int value;		
	IsModulus(int v) : value(v) {}
	bool operator()(int n) { return n % value  == 0; }
};

int main()
{
	std::vector<int> v = {1,2,3,4,5,6};

	int k = 3;

	// 객체를 생성해서 계속 사용한다면
	IsModulus m(k);		// 이름(m)이 있는 객체를 만든후
	auto p1 = std::find_if(v.begin(), v.end(), m );  // 인자로도 사용하고
													 // 이후 코드에서도 계속 m 이라는 이름으로 사용
	
	// 객체를 함수 인자등으로 한번만 사용한다면 "temporary" 형태로 만들어서 전달
	// temporary : 이름이 없는 객체, "클래스 이름(인자)"
	//			  
	auto p1 = std::find_if(v.begin(), v.end(),   IsModulus(k)  ); 
										// 이렇게 만들면, 인자로만 사용하고
										// 함수 호출이 종료되면 바로 파괴
}
