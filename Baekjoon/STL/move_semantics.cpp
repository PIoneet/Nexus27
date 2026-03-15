//std::vector 생명 연장

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

std::vector<int> getVectorLocal();

class MyVector
{
private:
    std::vector<int> myVec;
    
public:
    //MyVector(const int& a, const int& b) : myVec{a, b} {}
    MyVector(const int a, const int b) : myVec{a, b} {}

    std::vector<int> getVectorClass()
    {
        cout << myVec.data() << '\n';
        return myVec;
    }
};

int main()
{
    MyVector myVec(10, 2);
    std::vector<int> newVec = myVec.getVectorClass();
    cout << newVec.data() << endl;

    for(int n : newVec)
    {
        cout << n << '\n';
    }

}
//권한 위임의 중요한 예시다. myVec는 삭제되지만 그 주소값을 그대로 newVec에 전달한다.
std::vector<int> getVectorLocal()
{
    std::vector<int> myVec {10, 20, 30};
    cout << myVec.data() << endl;

    for(int n : myVec)
    {
        cout << n << '\n';
    }

    return myVec;
}
