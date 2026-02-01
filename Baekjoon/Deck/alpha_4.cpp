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
        
        if(dq.empty()){ 
            dq.push_front({i, input});
        }
        
        if(!dq.empty() && dq.front().index + L <= i){ //인덱스 전부 사용되면 제거
            dq.pop_front();
        }

        if(!dq.empty() && dq.back().val > input){ //새로 들어온 값보다 기존값이 크면 철저히 제거
            dq.pop_back();
        }

        if(dq.front().val > input){  
            dq.push_front({i,input});
        }
        else if(dq.front().val < input){
            dq.push_back({i, input});
        }else
            dq.push_front({i, input});
        
        cout << dq.front().val << " ";

    }

    return 0;

}