
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "character.h"
#include "input_utils.h"

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
            random_stats = random_partition(120, 6);
            character.stats = {random_stats[0], random_stats[1], random_stats[2], random_stats[3], random_stats[4], random_stats[5]};
            break;
        }
    }

    cout << "\n현재 스탯:" << endl;
    cout << "직업: " << character.job << endl;
    cout << "STR: " << character.stats[0] << endl;
    cout << "MEN: " << character.stats[1] << endl;
    cout << "TEC: " << character.stats[2] << endl;
    cout << "RES: " << character.stats[3] << endl;
    cout << "PER: " << character.stats[4] << endl;
    cout << "AGI: " << character.stats[5] << endl;

    
    cout << "\n=== 직업 선택 ===" << endl;
    cout << "1. 광부 (STR 특화)" << endl;
    cout << "2. 교주 (MEN 특화)" << endl;
    cout << "3. 해커 (TEC 특화)" << endl;
    cout << "4. 의사 (RES 특화)" << endl;
    cout << "5. 연설가 (PER 특화)" << endl;
    cout << "6. 암살자 (AGI 특화)" << endl;
    int jobChoice = get_valid_input(1, 6, "직업을 선택하세요: ");

    switch(jobChoice) {
        case 1: character.job = "광부"; break;
        case 2: character.job = "교주"; break;
        case 3: character.job = "해커"; break;
        case 4: character.job = "의사"; break;
        case 5: character.job = "연설가"; break;
        case 6: character.job = "암살자"; break;
    }
    cout << "\n" << character.job << "를 선택했습니다!" << endl;

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