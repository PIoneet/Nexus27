#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ios;
using std::cin;
using std::string;
using std::vector;


vector<string> map; 

void quadTree(int N, int row, int column);
bool checkMap(int N, int row, int column);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   
    int N;

    cin >> N;
    map.resize(N);
    for(int i = 0; i < N; i++){
        cin >> map[i];
    }

    quadTree(N, 0,0);
    

}

void quadTree(int N, int row, int column)
{ 
    int half = N/2;

    bool result = checkMap(N, row, column);
    if(result){
        cout << map[row][column];
        return;
    }

    cout << "(";
    quadTree(half, row, column);
    quadTree(half, row, column+half);
    quadTree(half, row + half, column);
    quadTree(half, row + half, column + half);

    cout << ")";
}

bool checkMap(int N, int row, int column)
{
    char target = map[row][column];

    for(int i=row; i<row+N; i++){
        for(int j=column; j<column+N; j++){
            if(map[i][j] != target){
                return false;
            }
        }
    }
    return true;
}