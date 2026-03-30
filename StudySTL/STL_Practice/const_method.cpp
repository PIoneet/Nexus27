#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Dog{
public:
    Dog(string name, int num) : name(name), num(num) {}
    
    const string& getName() const {
        return name;
    }
    //참조를 반환하며 변경하고 싶으면 복사하게함.

private:
    string name;
    int num{};
};

int main()
{
    const Dog dog("Hong Jae", 10);
    //string changeName = dog.getName(); // 똑같이 const string&
    //으로 받지 않아서 move가 아닌 복사가 일어난 것임. 

    const string& changeName = dog.getName();

    changeName = "Jaer";
    cout << changeName << endl;
}