#include <iostream>
#include <fstream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::unique_ptr;

/*
class Dog{
public:
    Dog() = default;
    Dog(int val) : ptr(&num), num(val) {
        cout << "Success" << endl;
    }

    static int& getSharedNum(const Dog& d){
        cout << d.num << endl;
        return shared_num;
    }
    // 일반 멤버 함수에 접근 불가. 

private:
    int* ptr;
    int num;
    inline static int shared_num{123456};

friend ostream& operator<<(ostream& os, const Dog& d){
    os << *(d.ptr) << "  " << d.num;
    return os;
}

};

*/

class Dog{
public:
    Dog() = default;
    Dog(int val) : p(new int{10}), num(val) {}

    //이동 생성자 스마트 포인터는 복사가 아니라 이동 즉 소유권을 건네주는 방식
    Dog(Dog&& other) noexcept : p(std::move(other.p)) {
        cout << "Move Constructor Called" << endl;
    }
    //소멸자 생성하면 default 이동생성자 생성 안된다. 

    // = 오버로딩 함수
    Dog& operator=(Dog&& other) noexcept { // noexcept는 보증서임. 
        if (this != &other) {
            p = std::move(other.p);
            //num = other.num;
        }
        return *this;
    }

private:
    unique_ptr<int> p;
    int num;

friend ostream& operator<<(ostream& os, const Dog& d){
    os << *(d.p) << "  " << d.num;
    return os;
}
};


const Dog& moveNum(const Dog& d)
{
    return d;
}

int main()
{
    Dog d(1000);
    cout << d << endl;
    Dog d2 = std::move(d); //대입 연산자를 이용한 이동

    Dog d4(std::move(d2)); // 이동 생성자를 이용한 이동
    cout << d4 << endl;

    cout << d << endl;
    cout << d2 << endl;
    //d랑 d2는 메모리 번지를 d4에게 뻇겨서 nullptr 상태가 되버린다. 

    

    Dog d3 = Dog(2000); 
    // -> 이름 없는 값(Rvalue)으로부터 이동시킨다. 
    // 컴파일러가 미리 보고 임시 객체랑 합쳐서 Dog d3(2000); 으로 바뀐다. 

    //cout << d3 << endl;







    //const Dog& result_d = moveNum(d);
    //const Dog& change_d = moveNum(Dog(200)); //이게 임시 객체 ;지나면 소멸자 호출
    // 참조자를 반환하기 때문에 컴파일러가 자동으로 객체 합치지 않는다.
    // change_d의 ptr은 죽은 임시 객체의 &num을 가리키기 때문에 복사 생성자를 직접
    //만들어서 고치지 않으면 쓰레기값을 가리킨다. 
    // 이래서 스마트 포인터를 써야 한다는 것이다. 

    //Dog d2 = d;
    //스마트 포인터는 복사 기능이 없다. 소유권은 오직 나 하나라는 의미를 띠기 때문에

    

    // &는 이름 있는 Lvalue를 참조하고 &&는 이름 없는 Rvalue를 참조한다.
    // 이름 있는 변수는 원본을 훼손하면 안되니까 복사를 하는 것이다.
    // 이름이 없는 임시객체면 어쩌피 ;만나서 사라지니까 이동시키겠다는 취지인거고


}