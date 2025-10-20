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
    
        cout << "\n캐릭터 이름: " << characters[i].name << endl;
        cout << "\n현재 스탯:" << endl;
        cout << "x(윗쪽): " << characters[i].stats[0] << endl;
        cout << "/(아랫쪽): " << characters[i].stats[1] << endl;
        cout << "-(왼쪽): " << characters[i].stats[2] << endl;
        cout << "+(오른쪽): " << characters[i].stats[3] << endl;

        cout << "\n랜덤으로 스탯을 조정 가능합니다." << endl;
        vector<int> random_stats;

        while(true) {
            cout << "스탯을 랜덤으로 조정하시겠습니까? (y/n): ";
            char choice;
            cin >> choice;
            if(choice == 'n' || choice == 'N'){
                break;
            }
            else{
                random_stats = random_generate(4);
                characters[i].stats = {random_stats[0], random_stats[1], random_stats[2], random_stats[3]};
                break;
            }
        }


        cout << "\n최종 전투력 수치:" << endl;
        cout << "이름: " << characters[i].name << endl;
        cout << "x(윗쪽): " << characters[i].stats[0] << endl;
        cout << "/(아랫쪽): " << characters[i].stats[1] << endl;
        cout << "-(왼쪽): " << characters[i].stats[2] << endl;
        cout << "+(오른쪽): " << characters[i].stats[3] << endl;

        cout << "\n" << characters[i].tileId << "번 캐릭터 커스터마이즈가 완료되었습니다!" << endl;
        
    
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        
    
    }
    created = true;

}



vector<int> random_generate(int parts) {
    vector<int> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-10, 10);

    int sum = 0;
    for (int i = 0; i < parts - 1; ++i) {
        int val = dis(gen);
        if(val == -0)
            val = 0;
        result.push_back(val);
        sum += val;
    }
    result.push_back(-sum); // 마지막 원소를 총합이 0이 되도록 맞춤
    return result;
}
