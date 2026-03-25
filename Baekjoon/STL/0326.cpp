#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <array>
#include <numeric>
#include <print>
#include <random>
#include <string>
#include <filesystem>
#include <ranges>

using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid{0, 999'9999}; //겹치는 랜덤 숫자 골라내기 1000만개중에서


int 오름차순(const void* a, const void* b) 
{
	return *(int*)a - *(int*)b;

}


class Dog {
public:
	Dog() {
		cout << "dog 생성" << endl;
	}
	~Dog() {
		cout << "dog 소멸" << endl;
	}
};

class smart {
private:
	Dog* p;
public:
	smart(Dog* p) : p{ p } {
		cout << "스마트 생성자 호출됨" << endl;
	}
	~smart() {
		cout << "스마트 소멸자 호출됨" << endl;
		delete p;
	}

};


// 문제 : 사용자가 원하는 개수만큼 int를 저장할 메모리를 확보하라. 
// 1부터 시작하는 int 값으로 채워라 메모리를
// 합계를 계산하여 출력하시오.


//문제: "main.cpp"에 있는 글자중에서 소문자는 모두 대문자로 바꿔(다른 건 그대로)
// "메인대문자.cpp"에 저장하시오.

//문제: 랜덤값을 갖는 int 1000만개를 메모리에 저장하라
//오름차순으로 정렬한 후 화면에 출력하라.

array<int, 1000'0000> a{ 1 }; //a는 데이터 세그먼트에 저장된 연속적 메모리
// [0] 부터 [999,9999]까지 연속적임.
int main()
{
	for (int& num : a)
		num = uid(dre);

	// 여기서 퀵 소트를 사용하여 오름차순으로 정렬하라. , callable type에 대하여
	
	qsort(a.data(), a.size(), sizeof(array<int, 1000'0000>::value_type),오름차순); //시작번지, 크기, 하나하나의 메모리 크기, []가 있다면 ranfom access가 가능하다는거임. 4번쨰 인자는 어떻게 정렬할지? 
	// 코드 세그먼트에 들어가는 함수를 원하는 것이다. 


	cout << "정렬 전 - 앞에서부터 1000개만 출력" << endl;
	for (int num: a | views::take(10) | views::reverse ){ // | 필터라고 부른다.
		print("{:8}", num);
	}

	//cout << sizeof(dre) << endl;

	/*
	ifstream in{ "main.cpp" };

	if (not in) {
		cout << "재확인" << endl;
		return 0;
	}

	ofstream out{ "메인대문자.cpp" }; //바이너리 한다고 이득이 없음

	//transform(원본 파일의 시작, 끝, 변신할 파일의 시작, 변신방법);
	transform(istreambuf_iterator<char>{in}, {}, ostreambuf_iterator<char>{out}, 
		[](char c) {
			c = toupper(c);
			return c;
		} 
	); //4번쨰 인자가 람다임 , 왜 return c해야되는지 char& c는 왜 안될까
	
	char c;
	
	in >> std::noskipws;
	while (in >> c) {
		if (islower(c)) {
		c = toupper(c);
		}
		out << c;
	}
	

	in >> std::noskipws;
	while (in >> c) {
		c = toupper(c);
		out << c;
	}
	*/
	
	


	//unique_ptr<Dog[]> p{ new Dog[10]}; // heap 얼마나 쓸수 있는지 저장 용량이, 얼마까지 데이터 담을 수 있냐 문제
	// 자원의 생명 주기를 p의 생명 주기와 일치시킨다.
	//smart p{ new Dog };

	// 여기에서 오류가 생겨서 return / exit은 절차가 서로 다르다. 
	// c++에서 return 문장으로 끝날떄 stack-unwinding 함을 보장 exit은 보장하지 않는다.
	// return응로 끝나면 지역에서 만든 객체가 소멸됨을 100퍼센트 보장한다. 그래서 int* p를 해제한다. 클래스 객체면 자동으로 소멸자 호출
	// RAII 구조로 만들어야 new int도 사라질 수 있다. 그게 스마트 포인터 , {}로 해야 explicit 

	




	/*
	return 0; 
	cout << "free store의 주소" << addressof(p) << endl;
	cout << "stack 의 주소" << p << endl; //정확히 어떤 주소를 가리키는지 확인하기
	cout << &p << endl;

	delete p;


	return 20260325;
	cout << "이 문장은 절대 출력되지 않는다" << endl;
	save("main.cpp"); // save는 절대 실행되지 않지만 스마트 포인터가 Dog는 무조건 다 해제해준다 -> 이게 RAII 구조, 자원관리의 자동화
	
	*/
	
}
