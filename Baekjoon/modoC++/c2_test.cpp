#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void ref_number(int& p)
{
    p = 100;
    cout << &p << endl;
    return;
}

int main()
{
    //데이터의 첫 주소값이 char*이면 쫘르륵 출력해주더라고

    const char* str = "Sun Hong Jae";

    char name[] = "Sun Hong Jae";
    char new_name[] = "Kim";
    
    // const 안붙이면 애초에 초기화도 불가하다.
    cout << str << endl; //문자열 리터럴이 그대로 출력되는건 ostream의 메소드가 단독처리하게 구성했기 때문
    cout << (void*)(str) << endl; 
    cout << (void*)(str+1) << endl;
    cout << (void*)(str+2) << endl;// 0x7ff 여기가 데이터 구역쪽 : 리터럴이 담기는 곳이다.
    cout << (void*)(str+3) << endl;
    cout << (void*)(str+4) << endl;
    cout << "///////////////" << endl;
    cout << name << endl;
    cout << (void*)name << endl;
    cout << (void*)(name+1) << endl;
    cout << (void*)(name+2) << endl;
    cout << (void*)(name+3) << endl;
    cout << (void*)(name+4) << endl << endl << endl;

    int a = 100;
    int* b = &a;

    //const int a; 정적 변수는 초기화가 필수다.



    
    /*
    int number = 10;
    cout << &number << endl;
    cout << number << endl;
    ref_number(number);
    //int& p = number;랑 완전 동일하다.
    cout << number << endl;
    */
}