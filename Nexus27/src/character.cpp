#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "character.h"
#include "input_utils.h"

using namespace std;

string color[COLOR_SIZE] = {"green", "red", "yellow", "blue", "magenta", "cyan"};

void customize_character(vector<GameCharacter>& characters) {
    pair<int, int> color_idx = random_generate_color(COLOR_SIZE);
    characters[0].color = color[(color_idx.first)];
    characters[1].color = color[(color_idx.second)];
    
    for(size_t i = 0; i < characters.size(); ++i) {
        //system("cls");
        int order = 1;
        //cout << "\n=== 캐릭터 커스터마이즈 ===" << endl;
        /*
        while(true){
            cout << "\n "<< order << "번 캐릭터의 이름을 입력하세요: ";
            if(cin.peek() == '\n') cin.ignore(); // 입력 버퍼 비우기
            getline(cin, characters[i].name);
            if(!characters[i].name.empty()) break;
            else system("cls");
        }
        */

        characters[i].startPower = random_generate({3,9}); //여기서 0이나 1안나오게 만들면
        
        /*
        cout << "\n최종 전투력 수치:" << endl;
        cout << "이름: " << characters[i].name << endl;
        cout << "초기 전투력: " << characters[i].startPower << endl;
        cout << "\n" << order << "번 캐릭터 커스터마이즈가 완료되었습니다!" << endl;
        */

        order++;

        /*cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();*/  
    }
    //created = true;

}



int random_generate(pair<int, int> range) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(range.first, range.second);
    int val = dis(gen);
    return val;
}

pair<int, int> random_generate_color(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, size - 1);
    pair<int, int> val;
    int first = dis(gen);
    int second = dis(gen);
    
    while (first == second) {
        second = dis(gen);
    }   
    val = {first, second};
    return val;
}
