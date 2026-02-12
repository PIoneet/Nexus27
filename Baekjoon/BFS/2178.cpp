#include <bits/stdc++.h>

using namespace std;


int main(){

    int inputHeight;
    int inputWidth;
    string input;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);   

    int board[500][500]; //저장할 2차원 배열
    int dist[500][500] = {0}; //방문 여부 확인
    queue<pair<int, int>> Q; 
    int row[4] = {0, 0, 1, -1}; //윗쪽, 아래쪽, 오른쪽, 왼쪽 순서
    int column[4] = {1, -1, 0, 0};
    

    cin>>inputHeight>>inputWidth;

    for(int i = 0; i<inputHeight; i++){ //2차원 배열에 저장하기.
        cin >> input;
        for(int j=0; j<inputWidth; j++){
            board[i][j] = (int)input[j] - '0'; //아스키값 0을 빼줘야함.
        }
    }

    Q.push({0,0});
    dist[0][0] = 1;
    while(!Q.empty()){
        pair<int, int> cur = Q.front();
        Q.pop();

        for(int dir = 0; dir<4; dir++){
            int nx = cur.first+row[dir];
            int ny = cur.second+column[dir];

            if(nx < 0 || nx >= inputHeight || ny < 0 || ny >= inputWidth){
                continue;
            }
            else if(board[nx][ny] == 0 || dist[nx][ny] != 0){
                continue;
            }
            else{
                dist[nx][ny] = dist[cur.first][cur.second] + 1;
                Q.push({nx, ny});
            }
        }
    }

    cout << dist[inputHeight-1][inputWidth-1] << endl;






    return 0;
}