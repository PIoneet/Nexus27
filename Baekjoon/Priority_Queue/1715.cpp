#include <bits/stdc++.h>

using namespace std;

//힙 자료구조는 push 할떄는 형제들끼리 정렬되지 않고 뒤죽박죽이다.
//하지만, push 할떄는 인덱스가 가장 큰 막내가 꼭대기로 올라가서 자식들이랑 다 비교하면서 정렬함.
// 결국 루트에는 항상 가장 작거나 큰값만 남는다. 그래서 이걸 힙정렬이라고 함.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    int input;
    int total = 0;
    priority_queue<int, vector<int>, greater<int>> pq;

    cin >> N;
    for(int i =0; i < N; i++){
        cin >> input;
        pq.push(input);
    }
    
    int count = 1;
    int temp = 0;
    while(!pq.empty()){
        if(count % 2 ==0){
            temp += pq.top();
            total += temp;
            pq.push(temp);
            //pop()을 늦게 하니까 temp push한게 바로 pop() 되는 오류 생기는거 아니냐? 생각 가능
            //근데 a =3 , b =5라 가정했을떄 a + b는 무조건 b보다는 크다. 둘다 양수이기 때문에
            // 그래서 그 걱정은 할 필요가 없다. 무조건 b가 pop될 수 밖에 없는 구조다.
        }
        else{
            temp = pq.top();
        }
        
        pq.pop();
        count++;
    }

    cout << total << endl;
    return 0;
}
