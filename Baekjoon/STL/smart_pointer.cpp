#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class smart_pointer_example 
{
private:
    std::unique_ptr<int> numPtr;

public:
    smart_pointer_example(int n) : numPtr{ std::make_unique<int>(n) } {}
    // 멤버 변수 초기화 리스트에서도 { }을 쓰는게 좋다. 

    int* getSmartPointer()
    {
        cout << *numPtr << '\n';
        //return numPtr;
        return numPtr.get();
    }
};

int main()
{
    smart_pointer_example smart_p(10);
    int* p = smart_p.getSmartPointer();

    cout << p << endl;
    *p = 100;
    cout << *p << endl;
}