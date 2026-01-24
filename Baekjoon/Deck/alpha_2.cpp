#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <algorithm>

// 문자열 쪼개기 파싱 -> sstream + getline


// RDRD 하면 결과가 아예 다르게 나옴. 명령어를 입력하는 서순을 고려해야됨.
using namespace std;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    deque<int> dq;
    string command;
    int size;
    int input_count;
    

    cin >> input_count;
    for(int i=0; i<input_count; i++){
        dq.clear();
        string arr_str;
        bool reversed = false;

        cin >> command;
        cin >> size;
        
        int d_count = count(command.begin(), command.end(), 'D');

        cin >> arr_str;
        arr_str = arr_str.substr(1, arr_str.size()-2); //대괄호 제거

        if(size - d_count< 0){ //d_count가 size보다 클때
            cout << "error\n";
            continue;
        }else{
            stringstream ss(arr_str);
            string input_num;
            
            for(int j = 0; j<size; j++){
                    getline(ss, input_num, ',');
                    dq.push_back(stoi(input_num));
            }

            for(int j=0; j<command.size(); j++){
                if(command[j] == 'R'){
                    reversed = !reversed;
                }
                else if(reversed && command[j] == 'D'){
                    dq.pop_back();
                }
                else{
                    dq.pop_front();
                }
            }
            cout << "[";
            
            if(reversed){ //역전 상황일때
                int dq_size = dq.size();
                for(int j=0; j<dq_size; j++){
                    cout << dq.back();
                    dq.pop_back(); //pop을 시켜야 순환이됨.
                    if(j != dq_size-1) cout << ",";
                }
            }else{
                int dq_size = dq.size();
                for(int j=0; j<dq_size; j++){
                    cout << dq.front();
                    dq.pop_front();
                    if(j != dq_size-1) cout << ",";
                }

            }
            cout << "]\n";
        }
        
        
    }

    return 0;
}
