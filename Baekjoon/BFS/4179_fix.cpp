#include <bits/stdc++.h>

using namespace std;

char board[1000][1000] = {0};
int dist[1000][1000] = {0};

int main(){
    int R; //세로(행의 수)
    int C; //가로(열의 수)
    char input;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int row[4] = {0, 0, -1, 1}; //오른쪽, 왼쪽, 상, 하
    int column[4] = {1, -1, 0, 0};
    queue<pair<int, int>> human;
    queue<pair<int, int>> fire;
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
            }
            else if(input == 'J'){
                board[i][j] = input;
                dist[i][j] = 1;
                human.push({i, j});
            }
            else if(input == 'F'){
                board[i][j] = input;
                fire.push({i, j});
            }
        }
    }

    //불을 먼저 처리한 이후에 지훈이를 처리? 

    while(!human.empty()){

        int fire_case = fire.size();
        for(int i = 0; i < fire_case; i++){
            pair<int, int> fire_cur = fire.front();
            fire.pop();

            for(int dir = 0; dir < 4; dir++){
                int nx = fire_cur.first + row[dir];
                int ny = fire_cur.second + column[dir];

                if(nx < 0 || nx >= R || ny < 0 || ny >= C){
                    continue;
                }
                else if(board[nx][ny] == '#' || board[nx][ny] == 'F'){
                    continue;
                }
                else{
                    board[nx][ny] = 'F';
                    fire.push({nx, ny});
                }
            }
        }

        int human_case = human.size();
        for(int k =0; k < human_case; k++){
            pair<int, int> human_cur = human.front();
            human.pop();

            for(int dir = 0; dir < 4; dir++){
                int nx = human_cur.first + row[dir];
                int ny = human_cur.second + column[dir];

                if(nx < 0 || nx >= R || ny < 0 || ny >= C){
                    cout << dist[human_cur.first][human_cur.second]<< endl;
                    return 0;
                }
                else if(dist[nx][ny] != 0 || board[nx][ny] == 'F'){
                    continue;
                }
                else{
                    dist[nx][ny] = dist[human_cur.first][human_cur.second] + 1;
                    human.push({nx, ny});
                }
            }
        }
        
    }

    cout << "IMPOSSIBLE" << endl;
    


    return 0;
}