#include <iostream>
#include <random>
#include <string>
#include <array>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::array;
using std::vector;

std::random_device rd;
std::default_random_engine dre(rd()); //정해진 seed 0을 쓰는 걸로 알고있음.

std::default_random_engine def; //정해진 seed 0을 쓰는 걸로 알고있음.
std::uniform_int_distribution uid{0, 100};
std::uniform_int_distribution<int> sid{'a', 'z'};

class Dog{
public:
    Dog(): num{uid(def)}{
        for(string& s: srr){
            s = sid(dre);
        }
    }

    string& getName(){
        return name;
    }

    int& getNum(){
        return num;
    }

    auto& getArr(){
        return arr;
    }

    int& getExample(){
        return example;
    }

    array<string, 100>& getSrr(){
        return srr;
    }

    ostream& operator<<(ostream& os){
        for(const int& num: arr){
            os << num << '\n';
        }
        return os;
    } 

private:
    string name;
    int num;
    array<int, 100> arr;
    array<string, 100> srr;
    int example;

friend ostream& operator<<(ostream& os, const Dog& dog){
    for(const string& name : dog.srr){
        os << name << '\n';
    }
    return os;
}
// cout이 아니라 os을 무조건 써야 하는 이유 -> 다형성 
//ostream은 cout도 받을 수도 있지만 cin, out(파일 출력 객체) 등 여러가지 받을 수 있다.
//cout을 단정지어서 사용하면 이건 콘솔 출력용으로 밖에 못쓰게 되는 것이다. 
// cout << myDog << "\n"; return os를 안하면 (cout 반환값) << '\n'; 에서 <<에 오류 발생

    
};

int main()
{
    Dog myDog;
    cout << myDog.getNum() << endl;
    cout << myDog.getName() << endl;
    array<int, 100>& arr2 = myDog.getArr();

    for(int& num: arr2){
        num = uid(dre);
    }

    myDog << cout;
    cout << "===== 다른 코드 =====" << '\n'; 
    cout << myDog.getExample() << endl; 
    // example은 사실 기본형 데이터 타입인데 초기화 안했다. 근데 접근 자체는 가능함. 
    // 물론 쓰레기값이 들어가긴 하지만

    array<string, 100>& new_srr = myDog.getSrr();

    cout << myDog;


    
    
    
    
    
    /*
    vector<int> ex_vec;
    //ex_vec.resize(10); 
    ex_vec.resize(1);
    ex_vec.reserve(10);

    // size가 1이라서 i=0일떄 들어가고 push_back()가 size를 계속 늘리다보니
    // 결국 무한 루프가 되버린다. 
    // capacity가 10을 넘어서면 힙의 다른 영역으로 복사되서 capacity가 20되면 이후 또 복사됨
    for(int i=0; i<ex_vec.size(); ++i){
        ex_vec.push_back(i);
        cout << ex_vec[i] << '\n';
    }
    */
    //string은 알아서 초기화 해주지만, array<int, 100>; 은 size만큼 자동으로 초기화 안함.
    //c++가 속력에 목숨거는 언어라서 array 자동으로 초기화하면서 느려질 수 있는 속력 떄문에
    //이런 배열 종류는 다 프로그래머한테 초기화를 맡긴 방식임. 
   
}