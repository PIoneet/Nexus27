#include <iostream>
#include <string>
#include <stack>

using namespace std;
int repeat(const string& input, int& k);

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string input;
    cin >> input;
    int k = 0;
    int result = 0;

    while(input.size()-1 > k){
        int temp = repeat(input, k);
        if(temp == 0){
            result = 0;
            break;
        }
        result = result + temp;
    }

    cout << result << endl;
    
    return 0; 

}


int repeat(const string& input, int& k){
    int sum;


    if(k < input.size() && input[k] == '('){
        k++;

        if(k < input.size() && input[k] == ')'){
            sum = 2;
            
            if(k+1 < input.size() && (input[k+1] == '(' || input[k+1] == '[')){
                k++;
                if(k >= input.size())
                    return 0;

                int temp = repeat(input, k);
                if(temp == 0)
                    return 0;
                else
                    return sum = sum + temp;
            }
            else{
                k++;
                return sum;
            }
        }
        else{
            int val = repeat(input, k); 
            if(k < input.size() && input[k] == ')'){
                k++;
                return sum = 2 * val;
            }
            else if(k < input.size() && ( input[k] == '(' || input[k] == '[') ){
                int temp = repeat(input , k);
                if(temp ==0)
                    return 0;
                
                if(k < input.size() && input[k] == ')'){
                    k++;
                    return sum = 2 * (val + temp);
                }else{
                    return 0;
                }
            }
            else
                return 0;
        }
        
    }
    else if(k < input.size() && input[k] == '['){
        k++;

        if(k < input.size() && input[k] == ']'){
            sum = 3;

            if(k+1 < input.size() && (input[k+1] == '(' || input[k+1] == '[')){
                k++;
                if(k >= input.size())
                    return 0;

                int temp = repeat(input, k);
                if(temp == 0)
                    return 0;
                else
                    return sum = sum + temp;
            }
            else{
                k++;
                return sum;
            }
        }
        else{
            int val = repeat(input, k);
            if(k < input.size() && input[k] == ']'){
                k++;
                return sum = 3 * val;
            }
            else if(k < input.size() && ( input[k] == '(' || input[k] == '[') ){
                int temp = repeat(input , k);
                if(temp ==0)
                    return 0;

                if(k < input.size() && input[k] == ']'){
                    k++;
                    return sum = 3 * (val + temp);
                }else{
                    return 0;
                }
            }
            else
                return 0;
        }
    }
    else{
        return 0;
    }

}