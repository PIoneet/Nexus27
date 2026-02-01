#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    deque<int> dq;

    int N;
    cin >> N;

    int L;
    cin >> L;
    if(L > N) L = N;
    int min_val;
    for(int i=0; i<N; i++){
        int input;
        cin >> input;
        dq.push_front(input);
        
        if(i==0)
            min_val = dq.front();

        if(dq.size() < L){
            if(dq[i] < min_val){
                min_val = dq[i];
            }
            cout << min_val << " ";
        }
        else if(dq.size() % L == 0){
            int min_val = dq.front();
            for(const int& val: dq){ //최솟값 구하는 로직
                if(val < min_val){
                    min_val = val;
                }
            }
            dq.pop_back();
            cout << min_val << " ";
        }
            
        
    }
    return 0;
}