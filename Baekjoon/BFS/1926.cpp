#include <bits/stdc++.h>

using namespace std;


int main(){
    int inputWidth;
    int inputHeight;
    int input;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int board[500][500]; //저장할 2차원 배열
    bool visited[500][500] = {false}; //방문 여부 확인
    queue<pair<int, int>> Q; 
    int row[4] = {0, 0, 1, -1}; //윗쪽, 아래쪽, 오른쪽, 왼쪽 순서
    int column[4] = {1, -1, 0, 0};
    int count = 0; //그림 총 개수
    int max_area = 0;


    cin>>inputHeight>>inputWidth;

    for(int i = 0; i<inputHeight; i++){ //2차원 배열에 저장하기.
        for(int j=0; j<inputWidth; j++){
            cin >> input;
            board[i][j] = input;
        }
    }

    for(int i = 0; i<inputHeight; i++){
        for(int j=0; j<inputWidth; j++){
            if(board[i][j] == 0 || visited[i][j] == true){
                continue;
            }
            else if(board[i][j] == 1){ //그림 발견
                visited[i][j] = true;
                count++;
                Q.push({i,j});
                int area = 0;
                
                while(!Q.empty()){ // 큐가 비었을떄 탈출
                    area++; // 그림의 넓이
                    pair<int, int> cur = Q.front();
                    Q.pop();

                    //탐색 로직에서 그림 하나 찾으면 다시 반복함.
                    for(int dir=0; dir<4; dir++){
                        int nx = cur.first+row[dir];
                        int ny = cur.second+column[dir];
                        if(nx < 0 || nx >= inputHeight || ny < 0 || ny >= inputWidth){
                            continue;
                        }
                        else if(board[nx][ny] == 0 || visited[nx][ny] == true){
                            continue;
                        }
                        else{ //좌표값이 1일떄
                            visited[nx][ny] = true;
                            Q.push({nx, ny});
                        }    
                    }
                }
                if(area > max_area){
                    max_area = area;
                }
            }
        }
    }
    cout << count << endl;
    cout << max_area << endl;
    return 0;
}