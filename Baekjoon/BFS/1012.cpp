#include <bits/stdc++.h>

using namespace std;


int main(){
    int T; //테스트 케이스
    int M; //가로
    int N; //세로
    int K; //배추 개수
    int inputX;
    int inputY;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int row[4] = {0, 0, 1, -1}; //오른쪽 왼쪽 하 상
    int column[4] = {1, -1, 0, 0};
    

    cin >> T;
    for(int t = 0; t < T; t++){


        int cabbets = 0;
        queue<pair<int, int>> Q;
        int board[50][50] = {0};
        bool visited[50][50] = {false};
        cin >> M >> N >> K;
        
        for(int i = 0; i < K; i++){
            cin >> inputX >> inputY;
            board[inputY][inputX] = 1;
        }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(board[i][j] != 1 || visited[i][j] == true){
                continue;
            }
            else{
                cabbets++;
                Q.push({i, j});
                visited[i][j] = true;

                while(!Q.empty()){
                    pair<int, int> cur = Q.front();
                    Q.pop();

                    for(int dir = 0; dir < 4; dir++){
                        int nx = cur.first + row[dir];
                        int ny = cur.second + column[dir];

                        if(nx < 0 || nx >= N || ny <0 || ny >= M){
                            continue;
                        }
                        else if(board[nx][ny] == 0 || visited[nx][ny] == true){
                            continue;
                        }else{

                            visited[nx][ny] = true;
                            Q.push({nx, ny});
                        }

                    }
                }
            }
        }
    }

    cout << cabbets << endl;  
    
    }

    return 0;

}