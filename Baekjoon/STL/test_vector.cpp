#include <iostream>
#include <vector>

using std::cout;
using std::endl;

int main()
{
    int a = 10;
    int* p = &a;
    std::vector<int> box;
    std::vector<std::vector<int>> boxes;
  
    box.resize(a);
    boxes.reserve(a);

    cout << box.size() << endl;
    cout << boxes.size() << endl;
    cout << box.capacity() << endl;
    cout << boxes.capacity() << endl;
    //resize는 size와 capacity를 둘다 늘림.
    //reserve는 capacity만

    cout << box.size() * sizeof(int) << endl;
    cout << boxes.size() * sizeof(std::vector<int>) << endl;
    //실제 힙영역에 저장된 box와 boxes의 size


    /*
    int num1[100];
    int num2[10];
    
    cout << sizeof(num1) << endl; //400
    cout << sizeof(num2) << endl; //40
    cout << sizeof(box) << endl;
    cout << sizeof(boxes) << endl;

    //vector는 스택 영역에서는 포인터3개 begin,end, capacity이거 3가지만가짐. 
*/

/*
    cout << sizeof(a) << endl;
    
    cout << &a << endl;
    cout << sizeof(&a) << endl;
    
    cout << p << endl;
    cout << sizeof(p) << endl;

    cout << &p << endl;
    cout << sizeof(&p) << endl;

    cout << *p << endl;
    cout << sizeof(*p) << endl;
*/
}

void sendBox(int* ptr)
{

}