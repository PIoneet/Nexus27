#include "../include/character.h"
#include "../include/input_utils.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void customize_character(GameCharacter& character) {
    cout << "\n=== 캐릭터 커스터마이즈 ===" << endl;
    
    while(true){
        cout << "\n캐릭터의 이름을 입력하세요: ";
        cin.ignore(); // 입력 버퍼 비우기
        getline(cin, character.name);
        if(!character.name.empty()) break;
        else system("cls");
    }
    
    
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



vector<int> random_partition(int total, int parts) {
    vector<int> cuts;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, total - 1);

    // 5개의 컷 위치를 랜덤하게 선택
    while (cuts.size() < parts - 1) {
        int cut = dis(gen);
        if (find(cuts.begin(), cuts.end(), cut) == cuts.end()) // 중복 방지
        //cut가 cuts에 없으면 cuts.end()를 반환함.
            cuts.push_back(cut);
    }
    cuts.push_back(0);
    cuts.push_back(total);
    sort(cuts.begin(), cuts.end());
    //서로다른 5개의 숫자와 앞에는 0 뒤에는 120이 정렬됨.

    vector<int> result;
    for (int i = 1; i < cuts.size(); ++i) {
        result.push_back(cuts[i] - cuts[i - 1]);
    }
    return result;
}