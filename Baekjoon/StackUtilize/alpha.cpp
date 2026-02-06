#include <iostream>
#include <string>
#include <stack>

using namespace std;


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string input;
    

    while(true){
        stack<char> S;
        getline(cin, input);
        if(input == ".")
            break;

        for(int i=0; i<input.size()-1; i++){ //마지막 온점은 제외
            if(S.empty()){}
            else if(S.top() == '(' && input[i] == ')'){
                S.pop();
                continue;
            }
            else if(S.top() == '[' && input[i] == ']'){
                S.pop();
                continue;
            }


            if(input[i] == '(' || input[i] == ')' || input[i] == '[' || input[i] == ']'){\
                S.push(input[i]);
            }
        }


        if(S.empty()){
            cout << "yes" << endl;
        }
        else{
            cout << "no" << endl;
        }
    }
    

    return 0;

}

