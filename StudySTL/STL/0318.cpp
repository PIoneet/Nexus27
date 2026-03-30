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

using namespace std;

default_random_engine dre;
uniform_int_distribution uid{ 0, 9999 };
uniform_int_distribution uidNameLen{ 10, 30 };
//uniform_int_distribution<char> uidChar{ 'a','z'};
uniform_int_distribution<int> uidChar{ 'a','z' };


//파일에 접근할 수 있는 방식이 2가지 있다. text,  binary 모드
// >>, <<(고급 입력, 고급 출력) read, write(lOW LEVEL) -> I/O 방식
// 어느 모드든 고급, 저급 출력 방식 써도됨. -> 확인해보자


class Dog { //메모리 라이아웃 확인해보자. 총 40바이튼데 마지막 4바이트는 패딩이라고 한다함.
public:
	Dog() { // num{uid(dre)}를 아래로 내리면 오류 없어짐.
		num = uid(dre); //여기선 {}를 쓸수 없는 이유가 있다함.
		int len{uidNameLen(dre)}; //size_t 쓸떄 축소변환 오류 생김.
		for (int i = 0; i < len; ++i) {
			name += uidChar(dre);
		}
		 // 10이상 30이하 임의의 알파벳으로 소문자만, 대문자 쓰는건 시험으로 나온다함
	}

	string getName() const {
		cout << " * ";
		return name;
	}

private:
	string name;
	int num{};

	friend ostream& operator<<(ostream& os, const Dog dog) {
		println(os,  "[{:4}] - {}", dog.num, dog.name); //println과 print의 차이점 알아보자.
		return os;
	}


};


/*
class Dog {

private: 
	string name;
	int num;

	friend ostream& operator<<(ostream& os, const Dog dog) {
		println(os, "[{:4}] - {}", dog.num, dog.name); //println과 print의 차이점 알아보자.
		return os;
	}

	friend istream& operator>>(istream& is, Dog& dog) {
		is.read((char*) & dog, sizeof(Dog));
		return is;
	}
};

*/

int main()
{
	array<Dog, 1000> dogs;

	sort(dogs.begin(), dogs.end(), [](const Dog& a, const Dog& b) {
		cout << "람다";
		return a.getName() < b.getName();
	});

	//for(const Dog& dog : dogs) {
	//	cout << dog << endl;
	//}

	//
	/*
	ifstream in{ "표준 string저장", ios::binary };

	if (not in) {
		return 202260318;
	}
	string s;

	in.read(  (char*)&s, sizeof(string));
	*/


	string s{ "12345678901233242342122312141" };
	ofstream out{ "표준 string저장"}; //string이 32바이트지

	//out.write((char*)&s, sizeof(string)); // &s
	//문제 바이너리 모드로 저장한 파일 "Dog백마리"에는 Dog 객체 100개가 Binary 파일에 저장되어있다.
	//Dog 객체는 파일의 write 함수를 사용하여 객체 크기 그대로 저장하였다.  <- 굉장히 중요한 문제다.

	// 파일을 읽어 array에 메모리에 저장하라. -> 다른 메모리에 저장하는 거 실습해보자.
	//객체 수 100개는 실행동안 변경되지 않는다. 

	//몇 객체인지 모를떄 확인할 수 있는 방법?
	//1. 파일 사이즈/ sizeof(Dog);
	//2. 직접 잃ㄱ어 몇개인지 센다.


	/*
	array<int, 100> read_dogs;
	Dog dogs[100];
	ifstream in{ "Dog백마리.bin", ios::binary };

	//cout << "Dog의 개수 - " << std::filesystem::file_size("Dog백마리") / sizeof(Dog) << endl;
	if (not in) {
		cout << "파일 읽어오기에서 문제 발생.." << '\n';
		return 20260318;
	}
	Dog dog;
	size_t cnt{};

	while (in >> dog) {
		++cnt;
	}
	
	while (in.read(reinterpret_cast<char*>(&dog), sizeof(Dog))) {
		++cnt;
	}
	
	cout << "Dog의 개수 - " << cnt << endl;
	
	*/


	//in.read((char*)dogs, 4000); // 이걸로 읽어오면 프로그램이 죽어버린다.
	//in.read(reinterpret_cast<char*>(read_dogs.data()), sizeof Dog * 100);
	/*
	for (const Dog& num : dogs) {
		cout << num << '\n';
	}

	*/
	/*
	//문제 Dog 100마리를 메모리에 저장하라. //연속적 메모리에 저장하면 바이너리 search가 빠름.
	//삭제가 안된다는 가정하엔 array에 넣는게 맞다.

	array<Dog, 100> dogs;
	for (const Dog& dog : dogs) { //const & 빠지면 아예 복사해서 돌리는거니까 개 나쁜 코드다.
		cout << dog << endl;
	}

	//dogs를 파일 "Dog백마리에 저장하라"
	// 파일 크기는 size(Dog) * dogs.size()이어야 한다. -> 바이너리 모드로 저장하라는 암시적 뜻

	ofstream out{ "Dog백마리.bin" };

	out.write(reinterpret_cast<char*>(dogs.data()), sizeof Dog * 100); //제공받은 시작 메모리부터 연속적으로 4000바이트까지 적는다.
	// 시작 메모리번지는 dogs.data() 이해하기 어렵다면 &dogs[0]이기도 하다.
	//파일 크기가 정확히 4000바이트가 나오는게 킥이다.
	//텍스트 모드로 하니까 4008바이트 나왔음.
	

	
	for (int i = 0; i < 10000; ++i) {
		cout << Dog() << endl;
	}
	*/

}


//contiguous(공간연속) <-> continuous(시간 연속)
// array는 공간연속 메모리
//비어있는 메모리가 없다 array는 40바이트가 100개이어서. 
//중간에 있는 메모리를 제거할 수는 없다. 메모리 유지관리가 쉽다.
//메모리 시작번지, 데이터 타입, 크기만 있어도 된다. 

// 