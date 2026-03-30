#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <print>

//비주얼 스튜디오는 소스 파일 안에 있는 파일은 다 단독으로 컴파일한다. 그래서 save.cpp 본문 코드는 main.cpp에 없음
//어쩌피 링커로 하나의 실행 파일로 통합됨.

using namespace std;

default_random_engine dre; //난수의 범위가 좁은 편이다.
uniform_int_distribution<int> uid{0, 9999};

class Dog;        // 전방 선언 foward declaration
// 컴파일 환경 release / x64
// 프로젝트 설정 일반 - /std::c++ latest
// - c/ c++ sdl 설정 아니요
//using namespace std; 는 가급적 사용하지 않는 편이 좋다.


// 템플릿 코드는 선언과 정의를 분리하지 않는다. 그래서 맨 꼭대기에 선언을 넣는 식으로 작성한다.
//void change(Dog&, Dog&); //이게 오버로딩이다

template <class T>
void change(T& a, T& b)
{
	T temp{ a }; 
	a = b;
	b = temp;
}
//자료형에 무관하도록 짜여진 알고리즘이 필요하다?



//int, double 같은 기본형 타입이나 std:: STL 객체는 알아서 메모리 정리해줌(소멸자 필요 없음)
// new로 동적 할당한 것들은 소멸자로 제거해야됨.
class Dog {
public:
	Dog() = default; // 소멸자는 쓸 필요가 없다는 것을 명심하자
	Dog(int n) : num{ n } {}  // explicit를 쓰면 int a =1 할때 문제 생김/

	/*operator int() { //friend를 써야됨. explicit 같은 문제가 생길 수 있어서
		return num;
	}*/

private:
	int num{};

friend ostream& operator<<(ostream& os, const Dog& dog) {
		return os << dog.num;
}

};
/*
template <>
void change<Dog>(Dog& a, Dog& b)
{
	cout << "템플릿을 확장하여 인간 컴파일러가 만든 코드" << '\n';
	Dog temp{ a };
	a = b;
	b = temp;
}
*/
void change(Dog& a, Dog& b) //타입에 묶여있어서 함수 호출 순위가 높다. 템플릿에 비해
{
	cout << "나는 global 함수야" << endl;
}

/*void change(Dog& a, Dog& b) //타입에 묶여있어서 함수 호출 순위가 높다.
{
	cout << "나는 그냥 함수야" << endl;
}*/

template <>   //템플릿의 특수화
void change<Dog>(Dog& a, Dog& b)
{
	cout << "who barked??" << '\n';
}

template <class T>
T add(const T& a,const T& b)
{
	return a + b;
}
string add(const string& a, const string& b)
{
	return string{ a + b }; //RVO 최적화 과정이라서 그냥 a + b 출력해도됨
}


int main()
{
	int num[1000];
	for (int i = 0; i < 100; ++i)
	{
		num[i] = uid(dre);
	}
	
	for (int num : num)
	{
		print("{:80}", num);
	}

	// 템플릿 함수 add로 실행되게 하자.
	cout << add(2026, 310) << endl;
	cout << add("2026년"s, " 3월 10일"s) << endl; //add가 string인자를 인식해야됨.

	// 컴파일할때 여기에는 주소 몇번지인지 알 수가 없음 기계어로 변환할때 
	int* p = new int[100]; //이렇게 주소를 설정해줘야 한다. 나머지 이름으로만 작성된 것들은 전부 메모리 번지라고 인식한다.
	//using Dog = int;
	int a{ 1 }, b{ 2 };
	change(a, b); //함수는 생략 가능한데 클래스는 절대 못한다 타입 추론을
	cout << a << " " << b << endl;

	Dog c{ 1 }, d{ 2 };
	change<Dog>(c, d); //함수 호출 우선수위가 있다.  이걸 보고 위 템플릿을 인스터화해서 컴파일하는 느낌인듯
	cout << c << " " << d << endl;
}


/*
void change(Dog& a, Dog& b)
{
	Dog temp{ a };
	a = b;     // a.operator = (b); 가 숨겨져 있음
	b = temp;
}

//위 오버로딩을 자동화할 수 있는 과정이 -> 템플릿이다.
*/

//c++은 일반화 프로그래밍 즉 템플릿의 원조다. -> Generic Proramming의 핵심 키워드
// 템플릿 함수, 템플릿 클래스, 템플릿 변수 3가지 만들 수 있다. 