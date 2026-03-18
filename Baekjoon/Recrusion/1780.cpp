#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::vector;

void nineTree(const vector<vector<int>>& papers, int N, int r, int c);
bool checkPaper(const vector<vector<int>>& papers, int N, int r, int c);


int minus_one{0};
int zero{0};
int one{0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int input;
    int N;

    cin >> N;
    //2차원 벡터는 행 줄 여러개가 있는 1차원 벡터의 집합이다.
    //그래서 행 줄을 []로 접근할려면 줄의 size를 만들어줘야함.
    //vector에서 ()은 줄 생성 , {}는 특정 값을 위한 방 생성이다.
    
    vector<vector<int>> papers(N);
    papers.reserve(N*N);

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> input;
            papers[i].push_back(input);
        }
    }

    nineTree(papers, N, 0, 0);

    cout << minus_one << '\n';
    cout << zero << '\n';
    cout << one << '\n';
    

}

void nineTree(const vector<vector<int>>& papers, int N, int r, int c)
{
    if(checkPaper(papers, N, r, c) == true){
        if(papers[r][c] == 0){
            zero++;
        }
        else if(papers[r][c] == 1){
            one++;
        }
        else if(papers[r][c] == -1){
            minus_one++;
        }

        return;
    }
    int thirds = N/3;

    nineTree(papers, thirds, r, c);
    nineTree(papers, thirds, r, c+thirds);
    nineTree(papers, thirds, r, c+(2*thirds));
    nineTree(papers, thirds, r+thirds, c);
    nineTree(papers, thirds, r+thirds, c+thirds);
    nineTree(papers, thirds, r+thirds, c+(2*thirds));
    nineTree(papers, thirds, r+(2*thirds), c);
    nineTree(papers, thirds, r+(2*thirds), c+thirds);
    nineTree(papers, thirds, r+(2*thirds), c+(2*thirds));
}


bool checkPaper(const vector<vector<int>>& papers, int N, int r, int c)
{
    int target = papers[r][c];
    for(int i=r; i<r+N; ++i){
        for(int j=c; j<c+N; ++j){
            if(papers[i][j] != target){
                return false;
            }
        }
    }

    return true;
}