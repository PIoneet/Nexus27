#include <bits/stdc++.h>

using namespace std;

int board[100][100][100] = {0};
int dist[100][100][100] = {0};

int main(){
    int M; //가로
    int N; //세로
    int Z; //z축
    int input;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    queue<tuple<int, int, int>> Q;
    int path = 0;
    int z_axis[6] = {1, -1, 0, 0, 0, 0};
    int row[6] = {0, 0, 0, 0, 1, -1}; //위, 밑, 왼, 오, 하, 상
    int column[6] = {0, 0, -1, 1, 0, 0};

    cin >> M >> N >> Z;

    for(int i =0; i<Z; i++){
        for(int j = 0; j<N; j++){ //행의 수 N이랑 비교해야되는 값
            for(int k=0; k<M; k++){
                cin >> input;
                board[i][j][k] = input;

                if(board[i][j][k] == -1){
                    dist[i][j][k] = -1;
                }
                else if(board[i][j][k] == 1){
                    Q.push({i, j, k});
                    dist[i][j][k] = 1;
                }
            }
        }
    }

    while(!Q.empty()){
        auto [cur_z, cur_x, cur_y] = Q.front();
        Q.pop();

        for(int dir = 0; dir < 6; dir++){
            int nz = cur_z + z_axis[dir];
            int nx = cur_x + row[dir];
            int ny = cur_y + column[dir];

            if(nz < 0 || nz >= Z || nx < 0 || nx >= N || ny < 0 || ny >= M){
                continue;
            }
            else if(dist[nz][nx][ny] != 0){
                continue;
            }
            else{
                dist[nz][nx][ny] = dist[cur_z][cur_x][cur_y] + 1;
                Q.push({nz, nx, ny});
            }
        }

        if(Q.empty()){
            path = dist[cur_z][cur_x][cur_y] -1;
        }

    }

    for(int i = 0; i < Z; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < M; k++){
                if(dist[i][j][k] != 0)
                    continue;
                else
                    path = -1;
            }
        }
    }
    

    cout << path << endl;

    
    return 0;
}