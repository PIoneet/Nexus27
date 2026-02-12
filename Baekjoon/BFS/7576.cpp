#include <bits/stdc++.h>

using namespace std;


int main(){

    int inputHeight;
    int inputWidth;
    int input;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);  

    int board[1000][1000]; //저장할 2차원 배열
    int dist[1000][1000] = {0}; //방문 여부 확인
    queue<pair<int, int>> Q; 
    int row[4] = {0, 0, 1, -1}; //윗쪽, 아래쪽, 오른쪽, 왼쪽 순서
    int column[4] = {1, -1, 0, 0};
    int path = 0;

    cin>>inputWidth>>inputHeight;

    for(int i = 0; i<inputHeight; i++){ //2차원 배열에 저장하기.
        for(int j=0; j<inputWidth; j++){
            cin >> input;
            board[i][j] = input;

            if(board[i][j] == 1){
                Q.push({i, j});
                dist[i][j] = 1;
            }
            else if(board[i][j] == -1){
                dist[i][j] = -1;
            }
                
        }
    }
    while(!Q.empty()){
        pair<int, int> cur = Q.front();
        Q.pop();

        for(int dir = 0; dir<4; dir++){
            int nx = cur.first+row[dir];
            int ny = cur.second+column[dir];

            if(nx < 0 || nx >= inputHeight || ny < 0 || ny >= inputWidth){
                continue;
            }
            else if(board[nx][ny] != 0 || dist[nx][ny] != 0){
                continue;
            }
            else{
                dist[nx][ny] = dist[cur.first][cur.second] + 1;
                Q.push({nx, ny});
            }
        }

        if(Q.empty()){
            path = dist[cur.first][cur.second] -1; //초기값 1은 뺴줘야함.
        }
    }

    for(int i = 0; i<inputHeight; i++){
        for(int j = 0; j<inputWidth; j++){
            if(dist[i][j] != 0)
                continue;
            else
                path = -1;
        }
    }

    cout << path << endl;
    return 0;

}