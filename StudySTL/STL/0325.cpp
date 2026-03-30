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
#include <memory>

using namespace std;

default_random_engine dre;
uniform_int_distribution uid{ 0, 9999 };
uniform_int_distribution uidNameLen{ 10, 30 };
//uniform_int_distribution<char> uidChar{ 'a','z'};
uniform_int_distribution<int> uidChar{ 'a','z' };

// string release 모드에서 32바이트
// vs에서는 SSO를 사용한다. 

//많은 데이터를 처리하기 위한 동적 메모리 할당( 동적: Dynamic Memory Allocation ) 
// static vs Dynamic : 코딩할떄 메모리가 결정됨. -> 컴파일 타입에 결정 / 실행 후에 필요한 메모리가 결정됨. -> 런타임에 결정
//메모리는 낮은 주소 (스택, 힙, 데이터, 코드) 높은 주소 컴파일 타임에서는 스택과 데이터를 사용, 런타임에서는 힙만 사용가능하다.
// 컴파일 타임에서는 데이터에 이름 붙여서 사용이 가능하다. 굳이 주소로 알려주지 않고 이름만 알려줘도 컴파일러가 알아서 작업해줌.
// 런타임 힙영역에서는 이름을 붙여줄 수가 없다. 
// 코드 상에서 이름은 무조건 다 주소라는 뜻이다. 



// 문제 : 사용자가 원하는 개수만큼 int를 저장할 메모리를 확보하라. 
// 1부터 시작하는 int 값으로 채워라 메모리를
// 합계를 계산하여 출력하시오.

int main()
{
	while (true) {
		//size_t number; //-값을 넣어도 num <0 걸러지지가 않는다 자동 변환되서,
		int number;
		int result{ 0 };

		cin >> number;
		if (number < 0) {
			cout << "음수 x" << endl;
			return 20260324; 
		}
		cout << "int가" << number << "확보되었습니다." << endl;

		
		//int* p; //안써야할 자료형이다. 
		// c++ 11 (Modern c++) 제데로 된 smart pointer가 있다.

		unique_ptr<int[]> p{new int[number]};// 템플릿 클래스다. , delete 시킬 필요가 없다. RAII 방식이다. ,지역 객체 p는 뭔일이 있어도 소멸해준다는 원칙 존재
		// 10000- 같이 입력하면 입력 버퍼에 문제 생김 -> 해결해보자.

		/*
		try {
			p.reset( new int[number]);
		}
		catch (std::exception& e) {// 이런거 무조건 cppreference에서 꼭 확인해봐야한다. 
			cout << "메모리 줄게 없다 " << e.what() << endl; // delete 하기전에 탈출하면 메모리 누수 가능해서 별로임.
			exit(20260324); // exit과 return의 차이점.
		}
		*/

		//이름을 붙일 수가 없음. 주소로 받아야됨. , free-store에 저장된다. 타입에 맞는 포인터를 돌려주기 때문에
		//애초에 크기를 주기 떄문에 운영체제는 시작 주소만 있으면 값을 저장가능하다.
		/*
		for (int i = 0; i < number; i++) {
			p[i] = i + 1;
		} 겁나 안좋은 코드다.
		*/

		iota(p.get(), p.get() + number, 1); //현재 p는 클래스의 객체라서 작동안된다. 메모리가 아니다.
		/*
		long long sum{}; //이런거 stl 알고리즘으로 해줘야 한다. 직접 하지 말라는 애기다.
		for (int i = 0; i < number; i++) { 합계구하는 알고리즘을 찾아봐야 한다는 방식으로 생각하자.
			sum += (*p) + i;
		}
		cout << sum << endl;
		*/
		
		//cout << accumulate(p, p + number, 0) << endl; 가독성이 많이 떨어져서 좋지 않다.
		long long sum = accumulate(p.get(), p.get() + number, 0LL); // {}보단 =이 낳다 초기화가 너무 복잡해지는 느낌이라?
		//0이라는 데이터에 따라서 달라진다. 0이면 int로 반환한다. 그래서 long long으로 타입 캐스팅 해줘야 한다.
		cout << sum << endl;


		/*
		arr.resize(number);

		for (int i = 1; i <= number; i++) {
			arr.push_back(i);
			result += i;
		}
		cout << result << endl;
		*/
	}

	int* p = new int;
	delete p;
	delete p;
	// 이거 왜 프로그램 사망하는건지 자원 반환 2번 하면 왜 안되는지

}

//sum이 int면 안된다. 일단
// 20억이 8GB다. delete를 쓰면 메모리 고갈 날 일이 없다. 
// delete 안하면 언젠간은 메모리가 터진다.

// 다음 시간 callable type에 대해 공부함.