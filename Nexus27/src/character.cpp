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
    cout << "x(윗쪽): " << character.stats[0] << endl;
    cout << "/(아랫쪽): " << character.stats[1] << endl;
    cout << "-(왼쪽): " << character.stats[2] << endl;
    cout << "+(오른쪽): " << character.stats[3] << endl;

    cout << "\n랜덤으로 스탯을 조정 가능합니다." << endl;
    vector<float> random_stats;

    while(true) {
        cout << "스탯을 랜덤으로 조정하시겠습니까? (y/n): ";
        char choice;
        cin >> choice;
        if(choice == 'n' || choice == 'N'){
            break;
        }
        else{
            random_stats = random_generate(4);
            character.stats = {random_stats[0], random_stats[1], random_stats[2], random_stats[3]};
            break;
        }
    }


    cout << "\n최종 전투력 수치:" << endl;
    cout << "이름: " << character.name << endl;
    cout << "x(윗쪽): " << character.stats[0] << endl;
    cout << "/(아랫쪽): " << character.stats[1] << endl;
    cout << "-(왼쪽): " << character.stats[2] << endl;
    cout << "+(오른쪽): " << character.stats[3] << endl;

    cout << "\n캐릭터 커스터마이즈가 완료되었습니다!" << endl;
}



vector<float> random_generate(int parts) {
    vector<float> result;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-10.0, 10.0);

    float sum = 0.0;
    for (int i = 0; i < parts - 1; ++i) {
        float val = dis(gen);
        if(val == -0.0)
            val = 0.0;
        float rounded = std::round(val * 10) / 10.0f;
        result.push_back(rounded);
        sum += rounded;
    }
    result.push_back(-sum); // 마지막 원소를 총합이 0이 되도록 맞춤
    return result;
}
