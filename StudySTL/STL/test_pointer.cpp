#include <iostream>

int* a()
{
    int* num = new int(10);
    std::cout << *num << '\n';
    return num;
}

int* b()
{
    int num{10};
    int* p = &num;
    std::cout << *p << '\n';
    return p;
}

int main()
{
    int* res = a();
    std::cout << *res << '\n';

    std::cout << *b() << '\n';
    delete res;
}