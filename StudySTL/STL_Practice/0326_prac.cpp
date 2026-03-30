#include <iostream>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::cout;
using std::endl;
using std::cin;
using std::vector;


// 문제: 사용자가 원하는 개수만큼 int를 저장할 메모리를 확보해라.
//1부터 시작하는 int값으로 채워라 메모리를
//합계를 계산하여 출력하시오

//std::vector 자체가 스마트 포인터의 역할도 가진다. 알아서 해제해준다. 
int main()
{
    int input;    
    cout << "please input Number: ";
    cin >>input;
    std::unique_ptr<int[]> p{new int[input]};

    itoa(p.get(), p.get() + input, 1);
    
    // 스마트 포인터의 타입은 가리키는 메모리의 타입을 요구한다. 
    //<int*>이면 가리키는 메모리 타입이 int**인 것이다.  int[]는 배열을 가리킨다.
    cout << p.get() << endl; // free store memory position
    cout << &p << endl; //smart pointer's address position

    
}