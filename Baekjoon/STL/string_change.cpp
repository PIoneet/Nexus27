#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main()
{
    string name = "Sun";

    cout << sizeof(name) << endl;
    cout << &name << endl;
    cout << (void*)name.data() << endl;
    cout << name.data() << endl;

    cout << endl;
    //name = "Hi, I'm Sun";
    name = "Hi, I'm Sun Hong Jae";

    cout << &name << endl;
    cout << (void*)name.data() << endl;
    cout << name.data() << endl;
    cout << sizeof(name) << endl;
    
}