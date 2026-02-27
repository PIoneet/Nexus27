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
            
            if(pq.size() < N){
                pq.push(input);
                continue;
            }
            else if(pq.top() > input){
                continue;
            }
            else if(pq.size() == N){
                pq.pop();
            }

            pq.push(input);
        }

    }

    cout << pq.top() << endl;


    return 0;
}