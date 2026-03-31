#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <string>
#include <print>
#include <ranges>
#include <chrono>

using namespace std;
// 호출가능한 타입 - callable type.
// 1. 함수
// 2. 람다 lambda
// 3. 클래스가 함수 호출 연산자를 오버로딩한 클래스의 객체 - functor
// 4. 멤버 함수 포인터

// 통합하여 function 클래스로 사용

int 오름차순(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;

}
//오름차순은 스택에서 데이터를 꺼내서 비교하는거다. 스택에다 돌아갈 번지 저장도 한다. 
// 스택에서 넣다 뺐다 하는 함수 호출 비용이 많아진다. 이 주요 비용을 오버헤드라고 한다. 


//  코드 새그먼트에 저장되는  함수
bool sort용오름차순(int a, int b)
{
	return a < b;
	//a < b  오름차순을 나타내는 기호. 
}

// 람다를 쓴 sort는 data랑 왔다갔다만한다. 따로 오름차순 호출하는 오버헤드 비용 없이.
// 그냥 sort와 람다 사이에 생기는 시간 차이가 이 오버헤드 비용이라고 볼 수 있다.

unsigned cnt{};

int 오름(const void* a, const void* b) {
	cout << "비교" << *(int*)a << "--" << *(int*)b << endl;
	++cnt;
	return *(int*)a - *(int*)b;

}

bool 오름2(int a, int b) {
	++cnt;
	return a < b;
}


void f()
{
	cout << "callable accept" << endl;
}
// () 함수 호출 연산자 -> 함수 호출 타입만 쓸 수 있음. 


void  점프()
{
	cout << "점프" << endl;
}

void 슬라이드()
{
	cout << "슬라이드" << endl;
}



array<int, 1000'0000> a{ 1 }; //a는 데이터 세그먼트에 저장된 연속적 메모리
// [0] 부터 [999,9999]까지 연속적임.
int main()
{
	// 클래스로 만드로 호출 타입 연산자()를 오버로딩한 것이다.
	[]() { // 컴파일러는 람다에 클래스를 씌워서 클래스로 만든다. 
		cout << "이름줘" << endl;
		} (); // 이것도 호출 가능하게 됐다. - 이름없는 함수 람다
	// 이름이 없으면 Lvalue가 아닌걸까? 이름이 없는데 호출됨?
	cout << typeid([]() {}).name() << endl; // 람다는 클래스였다.


	class XYZ {
	public:
		void operator()() {
			cout << "123" << endl;
		}
	};
	

	XYZ a;
	cout << typeid(a).name() << endl;



	void (*일번키)() = 점프;

	일번키();
	일번키();

	//설정
	일번키 = 슬라이드;
	일번키();


	/*
	int n;		  // sizeof, addressof, typeid
	
	cout << typeid(n).name() << endl;
	int a = n;
	cout << typeid(f).name() << endl;
	void (*b)() = f;

	b();
	// 왼쪽에 자료형 오른쪽에 이름 넣는게 정석이다. 
	// b =f 하면 8바이트짜리 주소를 담는다. 함수를 가리키니까 -> 함수 포인터
	// b는 얼마든지 다름 함수를 포인팅할 수 있다 자유롭다. 
	// 패드에서 다른 행동 할당하는 거랑 같은 맥락 
	(*f)(); // 이렇게 함수를 호출할 수 있다. 함수 포인터로 / f()는 좀 별로다.

	cout << typeid(b).name() << endl;
	
	f;

	*/




	//sort는 템플릿 알고리즘 함수다.  알고리즘 함수채로 찍어낸다. 
	// sort는 랜덤 iterator를 받는다. 
	// 소스코드를 그냥 inline으로 붙여놓는다. 
	/*
	int a[]{ 9,2,5,1,8,3,4,6,7,0 };       // 10*log10 = 40번 퀵소트하면
	sort(a, a + 10, [](int a, int b) {
		++cnt;
		cout << a << "---" << b << endl;
		return a < b;
		});   //sort 할떄는 27번 , 람다도 똑같이 27번이 나온다.
	cout << cnt << endl;
	
	*/
	// 함수들이 저장된 세그먼트 : 코드 세그먼트


	// std::sort로 천만개 정렬하는데 걸린 시간
	// begin() , end()에는 가리키는 데이터 타입을 알 수 있다. 
	// 끝 - 시작 / int size 하면 데이터의 크기를 알 수 있다.

	/*
	{
		// 1. 시작, 2. 끝 이터레이터 
		//sort는 가리키는 데이터 타입에 대한 정보를 너무 잘 안다.
		for (int& num : a)
			num = uid(dre);

		
		// 같은 메모리를 사용하는데 차이가 있다. 시간상
		auto start = chrono::high_resolution_clock::now();    //시간 재기 시작 
		//sort(a.begin(), a.end(), sort용오름차순);
		sort(a.begin(), a.end(), [](int a, int b) {
			return a < b;
			});
		//람다로 했을떄 시간이 훨씬 더 단축됐다.
		auto stop = chrono::high_resolution_clock::now();				  // 시간 끝
		

		//경과 시간이 나온다.  , 알고리즘 시간 재는데 쓰기 좋다.
		cout << "sort에 걸린시간 - " << chrono::duration_cast<chrono::milliseconds>(stop - start) << endl;


	}


	*/


	/*

	//qsort는 랜덤엑서스로 각요소에 O(1)로 접근 가능
	// qsort로 천만개 정렬하는데 걸린 시간
	//오름차순 함수를 O(n*logn)만큼 호출한다. 
	{ 
		for (int& num : a)
			num = uid(dre);

		// 여기서 퀵 소트를 사용하여 오름차순으로 정렬하라. , callable type에 대하여

		auto start = chrono::high_resolution_clock::now();    //시간 재기 시작 
		qsort(a.data(), a.size(), sizeof(array<int, 1000'0000>::value_type), 오름차순); //시작번지, 크기, 하나하나의 메모리 크기, []가 있다면 ranfom access가 가능하다는거임. 4번쨰 인자는 어떻게 정렬할지? 
		// 코드 세그먼트에 들어가는 함수를 원하는 것이다. 
		auto stop = chrono::high_resolution_clock::now();				  // 시간 끝
		//cout << "qsort에 걸린시간 - " << stop - start << endl;

		//경과 시간이 나온다.  , 알고리즘 시간 재는데 쓰기 좋다.
		cout << "qsort에 걸린시간 - " << chrono::duration_cast<chrono::milliseconds>(stop - start) << endl;


	}
	*/


	/*
	cout << "정렬 전 - 앞에서부터 1000개만 출력" << endl;
	for (int num : a | views::take(1000) | views::reverse) { // | 필터라고 부른다.
		print("{:8}", num);
	}
	*/


}

