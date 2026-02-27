#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    size_t N;
    int input;
    priority_queue<int, vector<int>, greater<int>> pq;

    cin >> N;
    for(size_t i =0; i<N; i++){
        for(size_t k=0; k<N; k++){
            cin >> input;
            if(pq.size() == N){
                pq.pop();
            }
            // N =2 일떄 10, 2, 12, 4입력시 에러 생김 정답은 10인데 4나옴.

            pq.push(input);
        }

    }

    cout << pq.top() << endl;


    return 0;
}