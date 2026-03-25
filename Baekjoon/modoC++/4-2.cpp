#include <iostream>

using std::cout;

void print(int input) {cout << input << '\n';};
void print(char input) {cout << input << '\n';};

int main()
{
    int a{10};
    char b{'c'};
    double c = 3.45;
    cout << (int)b << '\n';
    
    print(a);
    print(b);
    //print(c);
    //numeric 타입인 double이 char로도 형변환 가능하고 int로도 가능해서
}