#include <iostream>
#include <string>

using namespace std;

void str_recrusion(int n, string line);

int N;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   
    //system("chcp 65001");
    int count = 0;
    string line = "";
    cin >> N;
    
    str_recrusion(count, line);    
    return 0;

}

void str_recrusion(int n, string line){
    string default_line = "____" + line;
    if(n==0){
        default_line = "";
        cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다." << "\n";
    }
    else if(n==N){
        cout << default_line << "\"재귀함수가 뭔가요?\"" <<"\n";
        cout << default_line << "\"재귀함수는 자기 자신을 호출하는 함수라네\"" <<"\n";
        cout << default_line << "라고 답변하였지." << "\n";
        return;
    }

    cout << default_line << "\"재귀함수가 뭔가요?\"" << "\n";
    cout << default_line << "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어." << "\n";
    cout << default_line << "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지." << "\n";
    cout << default_line << "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"" << "\n";

    str_recrusion(++n, default_line);

    cout << default_line << "라고 답변하였지." << "\n";
}