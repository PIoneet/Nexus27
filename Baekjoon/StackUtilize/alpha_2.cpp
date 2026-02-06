#include <iostream>
#include <string>
#include <stack>

using namespace std;
int repeat(const string& input, int& k, stack<char>& S);

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    cin >> input;
    int k = 0;
    int result = 0;
    stack<char> S;

    while(input.size()-1 > k){
        int temp = repeat(input, k, S);
        if(temp == 0){
            result = 0;
            break;
        }
        result = result + temp;
    }

    cout << result << endl;
    
    return 0; 

}


int repeat(const string& input, int& k, stack<char>& S){
    int sum;
    if(input[k] == '('){
        S.push(input[k]);
        k++;
        if(input[k] == ')'){
            sum = 2;
            S.pop();
            if(input[k+1] == '(' || input[k+1] == '['){
                k++;
                return sum = sum + repeat(input, k ,S);
            }
            else{
                k++;
                return sum;
            }
        }
        else{
            sum = 2 * repeat(input , k , S);
            if(input[k] == ')'){
                S.pop();
                k++;
                return sum;
            }
            else
                return 0;
        }
        
    }
    else if(input[k] == '['){
        S.push(input[k]);
        k++;
        if(input[k] == ']'){
            sum = 3;
            S.pop();
            if(input[k+1] == '(' || input[k+1] == '['){
                k++;
                return sum = sum + repeat(input, k ,S);
            }
            else{
                k++;
                return sum;
            }
        }
        else{
            sum = 3 * repeat(input , k , S);
            if(input[k] == ']'){
                S.pop();
                k++;
                return sum;
            }
            else
                return 0;
        }

    }
    else{
        return 0;
    }
    


}