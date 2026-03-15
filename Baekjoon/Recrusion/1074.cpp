#include <iostream>

using std::ios;
using std::cin;
using std::cout;
using std::endl;

int z_recrusion(int N, int r, int c);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int r;
    int c;
    int total{0};
    cin >> N >> r >> c;

    total = z_recrusion(N, r, c);
    cout << total << '\n';
}

//N값에 따라 half를 구하고 재귀할때마다 N-1하는 구조임.
//어느 영역이냐에 따라 r이나 c값을 half만큼 빼서 조정함.
int z_recrusion(int N, int r, int c) //예시 2, 3, 1 -> 1,1,1
{
    if(N == 0){
        return 0;
    }

    int area = (1 << N) * (1 << N);
    int result{0};
    area = area / 4;
    int half = (1 << N) / 2;

    if(r >= 0 && r < half && c >= 0 && c < half){ //1사분면일떄
        result = z_recrusion(N-1, r, c);
        return result;
    }
    else if(r >= 0 && r < half && c >= half){ //2사분면일떄
        result = area + z_recrusion(N-1, r, c - half);
        return result;
    }
    else if(r >= half && c >= 0 && c < half){ //3사분면일떄
        result = (area * 2) + z_recrusion(N-1, r - half, c);
        return result;
    }
    else if(r >= half && c >= half){ //4사분면일떄
        result = (area * 3) + z_recrusion(N-1, r - half, c - half);
        return result;
    }
    else{
        return 0;
    }

}