#include <iostream>
#include <string>
#include <deque>

using namespace std;


struct A_i{
    int index;
    int val;
};

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    deque<A_i> dq;

    int N;
    cin >> N;

    int L;
    cin >> L;
    if(L > N) L = N;

    for(int i=0; i<N; i++){
        int input;
        cin >> input;
        
        // 1. 유효기간(L) 지난 데이터 앞쪽에서 삭제
        if(!dq.empty() && dq.front().index <= i - L){
            dq.pop_front();
        }

        //dq.empty()에서 조건문 성립 안하면 dq.front()를 읽지도 않고 나옴.

        // 2. [핵심 수정] 나보다 큰 녀석들은 뒤에서 "싹 다(while)" 삭제
        // if가 아니라 while입니다! 내가 짱 먹을 때까지 다 쳐냅니다.
        while(!dq.empty() && dq.back().val > input){
            dq.pop_back();
        }

        // 3. [핵심 수정] 나는 무조건 뒤로 입장
        // 앞(front)으로 들어가면 순서(index)가 꼬입니다.
        dq.push_back({i, input});
        
        // 4. 정답 출력 (맨 앞이 최솟값)
        cout << dq.front().val << " ";
    }

    return 0;
}