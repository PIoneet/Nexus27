#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Tower{
    int height;
    int name; //1부터 시작.
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int input_count;
    cin >> input_count;
    stack<Tower> S;

    for(int i=1; i <= input_count; i++){
        int height;
        cin >> height;

        while(!S.empty()){
            //break하는거 아니면 항상 스택에 1개 값만 있음.
            //시작부터 자기보다 큰값이 나오면 pop 
            if(S.top().height > height){ //push 하기전에 자기보다 큰 값 확인
                //높은 숫자는 활용 가치 있어서 남겨둠.
                cout << S.top().name << " ";
                break;
            }
            //pop을 하면 자동으로 S.top()이 바뀐다는 걸 활용했네.
            S.pop();
        }

        if(S.empty()){ //스택에 값이 남아있는 경우도 있어서
            cout << "0 ";
        }

        S.push({height, i});
    }
    return 0;
}