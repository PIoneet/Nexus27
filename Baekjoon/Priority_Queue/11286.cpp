#include <bits/stdc++.h>

using namespace std;

// priority_queue에 필요한 정렬 규칙을 정해주면됨.
struct cmp{
    // a가 부모, b가 push된 값을 의미함.
    bool operator()(int a, int b){
        //true 반환하면 스왑하라는 형태임.
        if(abs(a) == abs(b)){
            if(a > b){
                return true;
            }
            else{
                return false;
            }
        }
        else if(abs(a) > abs(b)){
            return true;
        }
        else{
            return false;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t input;
    int num;
    priority_queue<int, vector<int>, cmp> pq;
    // pq(); 이런 식으로 객체가 함수처럼 사용되는걸 함수 객체라 함.
    // 연산자 오버로딩임 이건
    cin >> input;
    for(int i = 0; i < input; i++){
        cin >> num;

        if(num == 0){
            if(pq.empty()){
                cout << 0 << endl;
            }
            else{
                cout << pq.top() << endl;
                pq.pop();
                //pop 후에도 다시 재정렬시킴.
            }
        }
        else{
            pq.push(num);
            //push에서는 cmp 규칙을 의거해서 힙 자료구조에 걸맞는 정렬을 수행함.
            // cmp(a, b) == true 하면 swap해라 이런식으로
        }
    
    }
    
    return 0;

}