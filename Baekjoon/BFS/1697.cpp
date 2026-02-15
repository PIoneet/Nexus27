#include <bits/stdc++.h>

using namespace std;


int main(){

    int N;
    int K;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);  

    int dist[100002] = {0}; //방문 여부 확인
    queue<int> Q; 
    int row[3] = {1, -1, 2}; 

    cin >> N >> K;
    Q.push(N);
    dist[N] = 0;

    while(dist[K] == 0){
        if(N == K){
            dist[K] = 0;
            break;
        }


        int cur = Q.front();
        Q.pop();

        for(int dir = 0; dir<3; dir++){
            int n;
            if(dir == 2){
                n = cur * row[dir];
            }
            else
                n = cur + row[dir];

            if(n < 0 || n > 100000){
                continue;
            }
            else if(dist[n] != 0){
                continue;
            }
            else{
                dist[n] = dist[cur] + 1;
                Q.push(n);
            }
        }
    }

    cout << dist[K] << endl;

    return 0;

}