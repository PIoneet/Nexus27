#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;;

int main()
{
    int a{3};
    int& another_a{a}; //참조자가 a를 가리킴.포인터처럼
    //int& another_another_a; 포인터처럼 null초기화는 안됨.
    
    int b{100};
    another_a = b;
    //another_a는 이미 참조자로써 a의 메모리를 가리킴.
    //b의 값을 a와 another_a가 가리키는 메모리에 복사했을 뿐임. 

    //참조자 another_a는 그냥 a가 가리키는 메모리를 참조할 수 있는 별칭 추가임.
    

    cout << a << endl;
    cout << another_a << endl;
    cout << b << endl << endl;

    another_a = 10;
    
    cout << a << endl;
    cout << another_a << endl;
    cout << b << endl << endl;
    
    b = 200;
    cout << a << endl;
    cout << another_a << endl;
    cout << b << endl << endl;


    cout << "//////////" << endl;

    string fake_text{"This"};
    string real_text = std::move(fake_text); //포인터 소유권 전달 이게 진짜 이동이다.

    cout << fake_text << endl;
    cout << real_text << endl;

    cout << (void*)fake_text.data() << endl;
    cout << (void*)real_text.data() << endl;

    cout << &fake_text << endl;
    cout << &real_text << endl;

    //null인 fake_text는 data의 포인터가 여전히 스택에 존재함.
    //16바이트 글자가 넘은 real_text의 data 포인터는 힙 영역에 존재
    //객체의 주소값 자체는 스택에 존재함. fake, real 모두

    //힙영역으로 가지 않는 이상 .data()의 메모리 번지는 객체 주소값 16바이트 뒤에 있다는거네



    cout << "/////////////" << endl;
    cout << "포인터 주소값" << endl;
    int* point_c;
    int d{100};
    int c{10};
    point_c = &d;

    //포인터는 아예 갈아탄다. 다른 메모리 번지로
    //참조자랑 포인터는 꽤 많이 다르구나. 
    cout << endl;
    cout << &c << endl;
    cout << point_c << endl;
    cout << &d << endl; // point_c와 &d가 같은 주소값을 지님.

    // 참조 변수의 주소값도 가리키는 변수의 주소값을 지님.
    //포인터 변수의 주소값은 가리키는 변수의 주소값과는 다름.

    cout << endl;
    cout << &c << endl;
    cout << &point_c << endl;
    cout << &d << endl;
    cout << &another_a << endl;
    cout << &a << endl;

    //d랑 point_c의 주소는 공백없이 연결되어 있는데
    //point_c에서 c사이에는 4바이트의 공백이 존재함.
    //매번 컴파일할떄마다. 할당받는 주소는 달라지더라도

    //출력해보면 가장 먼저 스택에서 선언한 a가 메모리 번지 위치가 가장 높음.
    //이는 스택이 위에서부터 아래로 주소를 주는 것을 보여줌.

}