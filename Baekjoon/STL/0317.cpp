#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <array>
#include <numeric>
#include <print>

//비주얼 스튜디오는 소스 파일 안에 있는 파일은 다 단독으로 컴파일한다. 그래서 save.cpp 본문 코드는 main.cpp에 없음
//어쩌피 링커로 하나의 실행 파일로 통합됨.

using namespace std;


//array<int, 1000'0000> a; 필요없음

int main()
{
	//문제 int 천개.bin"에는 1000개의 int값이 저장되어 있다.
	//파일은 바이너리 모드
	//메모리에 int 1000개 값을 읽어오세요.

	array<int, 1000> a;
	ifstream in{ "int 천개.bin", ios::binary };//바이너리로 읽을떄랑 텍스트랑 파일 크기 자체가 엄청 다름.
	in.read(reinterpret_cast<char*>(&a[0]), a.size() * sizeof(int));

	for (int num : a) { //range for라고 한다
		print("{:>40}", num); // 칸수 8칸에 맞춰서
	}



	//문제 text모드로 "int.txt"에 저장되어 있는 int값 중에서 가장 작은 값을 찾아 출력하라
	//int는 천만개가 확실해라는 정보가 추가적으로 주어짐.
	//1. 몇개인지는 읽기 전에 알 수 없다.
	//2. 파일 크기로부터 몇개인지 알 수 없다.

	//ifstream in이 in >> num; 고수준의 동작 바보 동작임. int가 아닌것까지 다 처리함.
	// 

	//문제 : int.txt 파일은 int 1000만개를 저장하는데 77MB 이상을 사용한다.
	//int  1000만개 저장하는데 필요한 메모리는 몇바이트인가?
	// 40메가 바이트에서 한 바이트도 가감되지 않음.

	//이 과정을 그림으로 설명함.
	//int num{ 33 };
	//out >> num; // out에 num이 어떻게 기록되는건지?
	// int가 어떤 순서로 저장되는지 엔디안 -> 좀 찾아보자.

	// 문제 int로 표현 가능한 모든 수를 파일에 text로 저장하였다. 수와 수는 한개의 공백 문자로
	//분리하였다. 
	//int 1개를 저장하기 위한 평균 바이트를 계산하라. 이거 시험 문제였음 텍스토 표현하면 메모리 오버헤드가 오진다.
	// 프로그램 실력이 엄청 향상될 수 있음
	//일반적으로 int 타입으로 메모리에 어떻게 저장되는지 텍스트로 저장하면 어떻게 저장되는지 알 필요가 있을듯.
	int num{ 12345 };
	

	// int 1억개를 파일에 저장 - binary I/O - 걸린시간 
	// int 1억개를 바이너리 모드로 파일에 저장 - binary I/O - 걸린시간 관찰함.
	// 텍스트 모드와 바이너리 모드의 차이점은 ?

	/*
	ofstream out{ "int억개", ios::binary };
	for (int i = 0; i < 1'0000'0000; ++i) {
		out.write(reinterpret_cast<char*>(&i), sizeof(int)); //밑바닥은 int 포인터없다 char*만 있지 c++ 프로그래머면 캐스팅 써야됨
	}
	
	
	//[문제] int 1000개를 다음과 같이 binary 모드로 파일 "int 천개.bin"에 기록하였다. 
	array<int, 1000> a;
	//바이너로 모드로 바꾸는 것보다 더 빠른 입출력 방식은 없다.
	iota(a.begin(), a.end(), 1); //1부터 시작하는 값으로 채워달라는 알고리즘임.
	
	ofstream out("int 천개.bin", ios::binary);
	out.write(reinterpret_cast<char*>(&a[0]), a.size() * sizeof(int)); // a.data() 써도됨.

	for (int num: a) { //range for라고 한다
		print("{:8}", num); // 칸수 8칸에 맞춰서
	}
	*/


	//고급 입출력 10을 전달하면 아스키 1 아스키 0이렇게 전달하는듯
	//저수준 입출력 방법: out >> num 처럼 하는게 아니라 밑바닥까지 내려가서 2바이트 씩 그대로 넘겨준다고?






	/*
	ifstream in{ "int값1000만개.txt" }; //처리해야 할 데이터 묶음이 이미 있는데 이걸 일일히 다 복사해서 작은 값 출력은 겁나 효율 별로임
	//읽을떄는 반드심 검사해라. 이 파일에서 데이터를 어떻게 읽는지 분석해보자
	if (not in) {
		cout << "파일 문제 발생" << endl;
		return 20260317;
	}
	
	size_t cnt{};
	for (int& num : a) {
		in >> num;
		++cnt;
	}
	cout << "읽은 개수: " << cnt << '\n';
	
	
	//cout << "최솟값: " << *min_element(istream_iterator<int>{in}, {}) << '\n'; //begin이 어떤 데이터를 가리키는지 분석해보자.
	cout << "최댓값: " << *max_element(istream_iterator<int>{in}, {}) << '\n'; //begin이 어떤 데이터를 가리키는지 분석해보자.
	
	
	priority_queue<int> pq;

	while (!in.eof()) {
		int num;
		if (in >> num) {
			//cout << num << '\n';
			pq.push(num);
		}
		else {
			continue;
		}
	}

	cout << pq.top() << endl;

	*/
}

// 위 코드는 txt에 있는 파일의 int를 일일이 다 복사하고 그걸 다 저장한 다음에 알고리즘 돌려서 처음부터 끝까지 확인했음.
// 비효율하고 또 비효율이다.
//애초에 복사를 하는 수고부터 안하는게 좋다.
//알고리즘한테 파일의 시작부터 끝을 줘서 확인하게 하는게 더 좋다.