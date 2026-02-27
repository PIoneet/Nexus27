#include <bits/stdc++.h>

using namespace std;

//우선순위 큐의 일회성이라는 성질에 의해 로직은 알맞았지만 실패

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    priority_queue<int> max_q;
    priority_queue<int, vector<int>, greater<int>> min_q;
    int input;

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> input;
        max_q.push(input);
        min_q.push(input);

        if(max_q.size() % 2 == 0){ //짝수일떄
            int target = max_q.size() / 2;
            int count = 1; 
            while(target != count){
                max_q.pop();
                min_q.pop();
                count++;
            }
            cout << min_q.top() << endl;
        }
        else if(max_q.size() % 2 == 1){ //홀수일떄
            int target = (max_q.size() / 2) + 1;
            int count = 1;

            while(target != count){
                max_q.pop();
                min_q.pop();
                count++;
            }

            cout << min_q.top() << endl;
        }
    }


    return 0;
}