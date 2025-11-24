#include "game_ui.h"
#include "input_utils.h"
#include "character.h"
#include <iostream>
#include <vector>

using namespace std;

void new_game(vector<GameCharacter>& players) {
    bool created = false;

    while (true) {
        system("cls");
        cout << "-----New Game-----" << endl;
        cout << "\n1. 캐릭터 선택" << endl;
        cout << "2. 캐릭터 생성" << endl;
        cout << "3. 게임 종료\n" << endl;
        int choice = get_valid_input(1, 3, "선택: ");

        if (choice == 1) {
            system("cls");
            // 생성된 캐릭터만 목록에 표시
            int created_count = 0;
            for (size_t i = 0; i < players.size(); ++i) {
                if (!players[i].name.empty()) ++created_count;
            }

            if (created_count == 0) {
                cout << "아직 생성된 캐릭터가 없습니다. 캐릭터를 먼저 생성하세요.\n";
                gameState = READY;
                break;
            } else {
                cout << "\n생성된 캐릭터 목록:" << endl;
                for (size_t i = 0; i < players.size(); ++i) {
                     
                    cout << endl;
                    cout << i+1 << ". 이름: " << players[i].name << "\n" << endl;
                    cout << "현재 스탯:" << endl;
                    cout << "초기 전투력: " << players[i].totalPower << endl;
                    cout << "-------------------" << endl;                    
                }
                gameState = INTRO;
                cout << "\n게임을 시작합니다: " <<"\n";
                break;
                
            }
        } else if (choice == 2) {
            // 빈 슬롯(이름이 빈 문자열)에만 캐릭터 생성
            if(!created){
                customize_character(players, created);
                cout << "모든 캐릭터가 생성되었습니다!\n";
                continue;
            } else {
                cout << "모든 슬롯에 캐릭터가 이미 생성되어 있습니다.\n";
                gameState = READY;
                break;
            }
        
        } else if (choice == 3) {
            cout << "게임을 종료합니다.\n";
            gameState = EXIT;
            break;
        }
    }
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
} 



void game_play(vector<GameCharacter>& players) {
    system("cls");
    if(gameState == EXIT)
        return;
    cout << "=== 게임 플레이 ===" << endl;
    cout << "\n"; 
    cout << 1 << "번 플레이어: " << players[0].name << " vs ";
    cout << 2 << "번 플레이어: " << players[1].name << "\n" << endl;
    cout << "1. 탐색 진행" << endl;
    cout << "2. 캐릭터 변경" << endl;
    cout << "3. 게임 종료\n" << endl;
    int choice = get_valid_input(1, 3, "선택하세요: ");
    system("cls");
    switch(choice) {
        case 1:
            players[0].opMap->move_map(players, id);
            if(gameScore == LOSE){
                gameScore = DRAW;
                players[0].opMap->initializeMap();
            }
            break;
        case 2:
            cout << "캐릭터 변경하기." << endl;
            gameState = READY;
            break;
        case 3:
            cout << "게임을 종료합니다." << endl;
            gameState = EXIT;
            break;
    }
}

