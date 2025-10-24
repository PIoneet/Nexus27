#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "character.h"
#include "input_utils.h"

using namespace std;

string color[COLOR_SIZE] = {"green", "red"};

void customize_character(vector<GameCharacter>& characters, bool& created) {
    for(size_t i = 0; i < characters.size(); ++i) {
        system("cls");
        cout << "\n=== 캐릭터 커스터마이즈 ===" << endl;
        
        characters[i].tileId = i + 1;
        characters[i].color = color[i];
        while(true){
            cout << "\n "<< characters[i].tileId << "번 캐릭터의 이름을 입력하세요: ";
            if(cin.peek() == '\n') cin.ignore(); // 입력 버퍼 비우기
            getline(cin, characters[i].name);
            if(!characters[i].name.empty()) break;
            else system("cls");
        }
        characters[i].totalPower = random_generate();

        cout << "\n최종 전투력 수치:" << endl;
        cout << "이름: " << characters[i].name << endl;
        cout << "초기 전투력: " << characters[i].totalPower << endl;

        cout << "\n" << characters[i].tileId << "번 캐릭터 커스터마이즈가 완료되었습니다!" << endl;
        
    
        /*cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();*/
    
    }
    created = true;

}



int random_generate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    int val = dis(gen);
    return val;
}
