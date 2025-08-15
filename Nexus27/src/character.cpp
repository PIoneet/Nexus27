#include "../include/character.h"
#include "../include/input_utils.h"
#include <iostream>

using namespace std;

void customize_character(GameCharacter& character) {
    cout << "\n=== 캐릭터 커스터마이즈 ===" << endl;
    
    cout << "캐릭터의 이름을 입력하세요: ";
    cin.ignore(); // 입력 버퍼 비우기
    getline(cin, character.name);
    
    cout << "\n현재 스탯:" << endl;
    cout << "STR: " << character.stats[0] << endl;
    cout << "MEN: " << character.stats[1] << endl;
    cout << "TEC: " << character.stats[2] << endl;
    cout << "RES: " << character.stats[3] << endl;
    cout << "PER: " << character.stats[4] << endl;
    cout << "AGI: " << character.stats[5] << endl;
    
    cout << "\n추가 스탯 포인트 10점을 배분할 수 있습니다." << endl;
    int remainingPoints = 10;
    
    while (remainingPoints > 0) {
        cout << "\n남은 포인트: " << remainingPoints << endl;
        cout << "1. STR (+1)  2. MEN (+1)  3. TEC (+1)  4. RES (+1)  5. PER (+1)  6. AGI (+1)  7. 완료" << endl;

        int choice = get_valid_input(1, 7, "어느 스탯을 올리시겠습니까? ");

        if (choice == 7) {
            break;
        } else if (choice >= 1 && choice <= 6) {
            character.stats[choice - 1]++;
            remainingPoints--;
            cout << "스탯이 증가했습니다!" << endl;
        } 
    }
    
    cout << "\n최종 스탯:" << endl;
    cout << "이름: " << character.name << endl;
    cout << "직업: " << character.job << endl;
    cout << "STR: " << character.stats[0] << endl;
    cout << "MEN: " << character.stats[1] << endl;
    cout << "TEC: " << character.stats[2] << endl;
    cout << "RES: " << character.stats[3] << endl;
    cout << "PER: " << character.stats[4] << endl;
    cout << "AGI: " << character.stats[5] << endl;
    
    cout << "\n캐릭터 커스터마이즈가 완료되었습니다!" << endl;
}
