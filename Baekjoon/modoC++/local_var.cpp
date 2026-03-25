#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int* localFunc()
{
    int a = 3;
    int* p = &a;
    //이렇게 허상 포인터가 잘못 가리켜서 런타임 에러 안뜨는 경우 있음. 
    //&a를 대놓고 반환하면 컴파일러가 감지해서 런타임 에러뜸
    return p;
}
// 런타임 에러 발생함.

int add(const int& a, const int& b)
{
    return a+b;
}
int main() 
{
    int* p = localFunc();
    int a{3}, b{4};
    cout << add(a, b) << endl; //중간에 함수 호출하니까 
    cout << *p << endl; // 3그대로 안나오고 이상한 값 들어감.
}