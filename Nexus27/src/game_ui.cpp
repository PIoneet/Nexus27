#include "game_ui.h"
#include "input_utils.h"
#include "character.h"
#include <iostream>

using namespace std;
string color[COLOR_SIZE] = {"red", "blue", "green"};

int start_game_ui() {
    system("cls"); 
    cout << "-----Nexus27-----" << endl;
    cout << "\n1. 새 게임" << endl;
    cout << "2. 불러오기" << endl;
    cout << "3. 도움말" << endl;
    cout << "4. 게임 종료\n" << endl;
    
    return get_valid_input(1, 4, "Enter your choice: ");
}

GameCharacter* new_game(vector<GameCharacter>& players) {
    
    while (true) {
        system("cls");
        cout << "-----New Game-----" << endl;
        cout << "\n1. 캐릭터 선택" << endl;
        cout << "2. 캐릭터 생성" << endl;
        cout << "3. 뒤로 가기\n" << endl;
        int choice = get_valid_input(1, 3, "선택: ");

        if (choice == 1) {
            // 생성된 캐릭터만 목록에 표시
            int created_count = 0;
            for (size_t i = 0; i < players.size(); ++i) {
                if (!players[i].name.empty()) ++created_count;
            }
            if (created_count == 0) {
                cout << "아직 생성된 캐릭터가 없습니다. 캐릭터를 먼저 생성하세요.\n";
            } else {
                cout << "\n생성된 캐릭터 목록:\n" << endl;
                for (size_t i = 0; i < players.size(); ++i) {
                    if (!players[i].name.empty()) {
                        cout << i+1 << ". 이름: " << players[i].name << ", 직업: " << players[i].job << "\n" << endl;
                        cout << "현재 스탯:" << endl;
                        cout << "STR: " << players[i].stats[0] << endl;
                        cout << "MEN: " << players[i].stats[1] << endl;
                        cout << "TEC: " << players[i].stats[2] << endl;
                        cout << "RES: " << players[i].stats[3] << endl;
                        cout << "PER: " << players[i].stats[4] << endl;
                        cout << "AGI: " << players[i].stats[5] << endl;
                    }
                }
                cout << "\n선택할 캐릭터 번호: ";
                int sel;
                cin >> sel;
                // 선택된 번호가 생성된 캐릭터인지 확인
                if (sel >= 1 && sel <= (int)players.size() && !players[sel-1].name.empty()) {
                    cout << "게임을 시작합니다: " << players[sel-1].name << "\n";
                    gameState = INTRO;
                    return &players[sel-1];
                    
                } else {
                    cout << "잘못된 선택입니다.\n";
                }
            }
        } else if (choice == 2) {
            // 빈 슬롯(이름이 빈 문자열)에만 캐릭터 생성
            bool created = false;
            for (size_t i = 0; i < players.size(); ++i) {
                if (players[i].name.empty()) {
                    GameCharacter newChar(&globalMap, color[i]);

                    customize_character(newChar);
                    players[i] = newChar;
                    cout << "캐릭터가 생성되었습니다!\n";;
                    created = true;
                    break;
                }
            }
            if (!created) {
                cout << "모든 슬롯에 캐릭터가 이미 생성되어 있습니다.\n";
            }
        } else if (choice == 3) {
            cout << "뒤로갑니다.\n";
            gameState = READY;
            return nullptr;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void load_game() {
    cout << "게임 불러오기 기능은 아직 구현되지 않았습니다." << endl;
}

void help() {
    cout << "도움말 기능은 아직 구현되지 않았습니다." << endl;
}

void exit_game() {
    cout << "게임을 종료합니다." << endl;
}   

void game_intro() {
    cout << "\n========================================" << endl;
    cout << "Welcome to our World called Menzo" << endl;
    cout << "========================================" << endl;
    cout << "어둠 속에서 깨어난 당신..." << endl;
    cout << "이곳은 신비로운 던전의 입구입니다." << endl;
    cout << "용기를 내어 모험을 시작해보세요!" << endl;
    cout << "========================================" << endl;
    //대사 넘어갈떄마다 음성 소리 나오는 것도 재밌을듯.
}

// 단일 캐릭터 플레이용 오버로드
void game_play(GameCharacter& gamePlayer) {
    system("cls");
    cout << "=== 게임 플레이 ===" << endl;
    cout << "\n플레이어: " << gamePlayer.name << "\n" << endl;
    cout << "1. 탐색 진행" << endl;
    cout << "2. 인벤토리 확인" << endl;
    cout << "3. 상태 확인" << endl;
    cout << "4. 캐릭터 변경" << endl;
    cout << "5. 게임 종료\n" << endl;
    int choice = get_valid_input(1, 5, "선택하세요: ");
    system("cls");
    switch(choice) {
        
        case 1:
            gamePlayer.pos = operation_map(gamePlayer);

            break;
        case 2:
            cout << "인벤토리 기능은 아직 구현되지 않았습니다." << endl;
            break;
        case 3:
            cout << "상태 확인 기능은 아직 구현되지 않았습니다." << endl;
            break;
        case 4:
            cout << "캐릭터 변경하기." << endl;
            currentPlayer = new_game(player);
            break;
        case 5:
            cout << "게임을 종료합니다." << endl;
            gameState = EXIT;
            break;
    }
}

