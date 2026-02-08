#include <iostream>
#include <string>

using namespace std;

string input;

int repeat(int& k) {
    if (k >= input.size()) return 0;

    char open = input[k];
    char close = (open == '(') ? ')' : ']';
    int multiplier = (open == '(') ? 2 : 3;

    if (open == '(' || open == '[') {
        k++; // 여는 괄호 패스

        // 1. 바로 닫히는 경우 (자식 없음)
        if (k < input.size() && input[k] == close) {
            k++; // 닫힐떄는 결과적으로 k + 2;
            return multiplier;
        }
        // 2. 자식이 있는 경우
        else {
            int inner_sum = 0;

            // ⭐ [여기가 핵심!] ⭐
            // 형제가 몇 명이든 닫는 괄호가 나올 때까지 계속 더합니다.
            while (k < input.size() && input[k] != close) {
                // 엉뚱한 닫는 괄호 체크
                if (input[k] == ')' || input[k] == ']') return 0;

                int sibling_val = repeat(k); // 형제 하나 계산
                if (sibling_val == 0) return 0;
                
                inner_sum += sibling_val; // 합계에 누적 (val + temp + ...)
            }

            // 루프가 끝났으면 내 짝꿍 닫는 괄호 확인
            if (k < input.size() && input[k] == close) {
                k++; 
                return multiplier * inner_sum;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> input;
    
    int k = 0;
    int result = 0;

    // Main 함수 Loop: 가장 바깥쪽 형제들 처리
    while(k < input.size()){
        if(input[k] == ')' || input[k] == ']') { // 찌꺼기 괄호 방지
            result = 0; 
            break; 
        }
        
        int temp = repeat(k);
        if(temp == 0){
            result = 0;
            break;
        }
        result += temp;
    }

    cout << result << endl;
    return 0;
}