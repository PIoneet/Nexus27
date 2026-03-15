#include <iostream>

using std::cout;
using std::ios;
using std::cin;
using std::endl;

//size_t나 unsigned int는 0보다 작아지면 양수 최대값이 되서 오류생기기 좋음.
// 음수 안써도 int도 결국 4바이트 차지하는 메모리 공간이라 size_t쓴다고 메모리 아끼는것도 아님.

long long findValue(long long A, long long B, long long C);
//와 로직 매우 천재적이네. 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   
    
    long long A;
    long long B;
    long long C;
    cin >> A >> B >> C;
    A = A % C; //나머지를 함수에 넘긴다.
    long long result = findValue(A, B, C);

    cout << result << endl;
    return 0;
}
// 함수를 21억번이나 재귀 호출하면 스택에 콜 스택이 계속 쌓여서 오버플로우 일어난다.
// 어쩌피 같은 값을 B만큼 곱하는 문제라 반으로 분할해서 재귀 호출하는게 지린다.

long long findValue(long long A, long long B, long long C){
    if(B == 1){
        return A % C;
    }

    long long half = findValue(A, (B/2), C);

    half = (half * half) % C;

    if(B % 2 == 0){
        return half;
    }
    else{
        //홀수면 5/2 할떄 3이 아닌 2가되기 때문에 한칸 더 앞의 요소를 계산해줘야함.
        return (half * A) % C;
    }
    
}