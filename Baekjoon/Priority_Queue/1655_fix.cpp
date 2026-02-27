#include <bits/stdc++.h>

using namespace std;

// endl 보다 "\n"이 몇배는 더 효율적이게 줄바꿈 가능하다.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    priority_queue<int> max_q; //중간값보다 작은 value
    priority_queue<int, vector<int>, greater<int>> min_q;
    //중간값보다 큰 value 모음
    int input;

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> input;
        if(max_q.size() == min_q.size()){
            max_q.push(input);
        }
        else if(max_q.size() > min_q.size()){
            min_q.push(input);
        }

        if(min_q.size() == 0){
            cout << max_q.top() << "\n";
            continue;
        }
        else if(max_q.top() > min_q.top()){
            int max_temp = max_q.top();
            int min_temp = min_q.top();

            max_q.push(min_temp);
            min_q.push(max_temp);
            max_q.pop();
            min_q.pop();
        }
        
        cout << max_q.top() << "\n";

    }


    return 0;

}