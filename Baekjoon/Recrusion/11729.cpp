#include <iostream>

using std::ios;
using std::cin;
using std::cout;
using std::endl;

void hinoi_top(int N, int start, int end, int via);



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);     
    int result;
    int N; 
    cin >> N;
    result = (1 << N) - 1;
    cout << result << '\n';
    hinoi_top(N, 1, 3, 2);

}
// start와 end를 출력하는 초기 조건을 기준으로 재귀를 돌면서
// start와 end에는 원판이 이동하는 출발지와 목적지를 인자로 준다.
// 개인적으로 N == 1 일때라는 초기 조건을 찾는것
// 그리고 N == 2일떄 N == 1로 재귀 함수 호출될떄 변화를 인지해야됨.

// start는 장대에 있는 원판의 개수가 아니라 장대 넘버였음.
void hinoi_top(int N, int start, int end, int via)
{
    if(N == 1){
        cout << start << " " << end << '\n';\
        return;  
    }

    hinoi_top(N-1, start, via , end);
    cout << start << " " << end << '\n'; 

    hinoi_top(N-1 , via , end, start);
}

