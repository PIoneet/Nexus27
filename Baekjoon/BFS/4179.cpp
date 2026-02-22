#include <bits/stdc++.h>

using namespace std;

char board[1000][1000] = {0};
int dist[1000][1000] = {0};

int main(){
    int R; //세로(행의 수)
    int C; //가로(열의 수)
    char input;
    int poss = 0;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int row[4] = {0, 0, -1, 1}; //오른쪽, 왼쪽, 상, 하
    int column[4] = {1, -1, 0, 0};
    queue<pair<int, int>> Q;
    int path = 0;

    cin >> R >> C;

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> input;
            if(input == '#'){
                board[i][j] = input;
                dist[i][j] = -1;
            }    
            else if(input == '.'){
                board[i][j] = input;
                dist[i][j] = 0;
            }
            else if(input == 'J'){
                poss++;
                board[i][j] = input;
                dist[i][j] = 1;
                Q.push({i, j});
            }
            else if(input == 'F'){
                board[i][j] = input;
                dist[i][j] = 1;
                Q.push({i, j});
            }
        }
    }


    while(!Q.empty()){
        bool fire = true;
        pair<int, int> cur = Q.front();
        Q.pop();

        if(board[cur.first][cur.second] == 'J'){
            poss--;
            board[cur.first][cur.second] = '.';
            fire = false;
        }


        for(int dir = 0; dir < 4; dir++){
            int nx = cur.first + row[dir];
            int ny = cur.second + column[dir];
            

            if(!fire){ //J부터 처리한다. 

                if(nx < 0 || nx >= R || ny < 0 || ny >= C){
                    poss++;
                    while(!Q.empty())
                        Q.pop();
                }
                else if(dist[nx][ny] != 0){
                    continue;
                }
                else{
                    dist[nx][ny] = dist[cur.first][cur.second] + 1;
                    Q.push({nx, ny});
                    board[nx][ny] = 'J';
                    poss++;
                }
            
            }   
            else{ //불일떄

                if(nx < 0 || nx >= R || ny < 0 || ny >= C){
                    continue;
                }
                else if(dist[nx][ny] == -1 || board[nx][ny] == 'F'){
                    continue;
                }
                else if(board[nx][ny] == 'J'){
                    dist[nx][ny] = 1;
                    board[nx][ny] = 'F';
                    poss--;
                    Q.push({nx, ny});
                }
                else{
                    dist[nx][ny] = 1;
                    board[nx][ny] = 'F';
                    Q.push({nx, ny});
                }

            }
        
        }

        if(poss <= 0){
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }

        if(Q.empty()){
            path = dist[cur.first][cur.second];
        }

    }

    cout << path << endl;


    
    
    
    return 0;

}