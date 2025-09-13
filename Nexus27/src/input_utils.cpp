#include "input_utils.h"
#include <iostream>

using namespace std;

// 타입 검사와 범위 검사를 한번에 하는 함수
int get_valid_input(int min, int max, const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        
        // 타입 검사
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요." << endl;
            continue;
        }
        
        // 범위 검사
        if (input < min || input > max) {
            cout << min << "~" << max << " 사이의 숫자를 입력해주세요." << endl;
            continue;
        }
        
        return input; // 유효한 입력이면 반환
    }
}
