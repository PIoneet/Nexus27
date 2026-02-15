#include <bits/stdc++.h>

using namespace std;

//1000,000 x 4바이트 = 4MB정도 된다 그니까 총합 약 8MB이다. 
//스택 용량이 1MB 정도라서 힙 영역에 선언해야됨. 스택 오버플로우 생김.
int board[10000][100] = {0};
int dist[10000][100] = {0}; // M <= 100 , N <= 100 , H <= 100이라서

int main(){
    int M; //가로
    int N; //세로
    int Z; //z축
    int input;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
    queue<pair<int, int>> Q;
    int path = 0;

    cin >> M >> N >> Z;
    // 이런 식으로 입력받고 변수 값으로 초기화하는건 오류 생길 수 있음.
    int row[6] = {0, 0, 1, -1, N, -N}; //왼, 오, 하, 상, 위, 밑
    int column[6] = {-1, 1, 0, 0, 0, 0};

    int Y = N * Z;
    for(int i =0; i < Y; i++){
        for(int j=0; j < M; j++){
            cin >> input;
            board[i][j] = input;

            if(board[i][j] == -1)
                dist[i][j] = -1;
            else if(board[i][j] == 1){
                Q.push({i, j});
                dist[i][j] = 1; //나중에 1뺴줘야됨 초기값 1이라
            }
        }
    }

    while(!Q.empty()){
        pair<int, int> cur = Q.front();
        Q.pop();

        for(int dir =0; dir < 6; dir++){

            int nx = cur.first + row[dir];
            int ny = cur.second + column[dir];

            if(nx < 0 || nx >= Y || ny < 0 || ny >= M){
                continue;
            }
            else if((nx != 0) && (nx % N == 0)){
                continue;

            }else if((nx != 0) && (nx % N == N-1)){
                continue;

            }
            else if(dist[nx][ny] != 0){
                continue;
            }
            else{
                dist[nx][ny] = dist[cur.first][cur.second] + 1;
                Q.push({nx, ny});
            }
        }

        if(Q.empty()){
            path = dist[cur.first][cur.second] -1;
        }
    }

    for(int i = 0; i<Y; i++){
        for(int j = 0; j<M; j++){
            if(dist[i][j] != 0)
                continue;
            else
                path = -1;
        }
    }

    cout << path << endl;

    return 0;

}