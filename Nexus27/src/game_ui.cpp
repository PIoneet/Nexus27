#include "../include/game_ui.h"
#include "../include/input_utils.h"
#include "../include/character.h"
#include "../include/game_map.h"
#include <iostream>

using namespace std;

int start_game_ui() {
    cout << "-----Nexus27-----" << endl;
    cout << "1. 새 게임" << endl;
    cout << "2. 불러오기" << endl;
    cout << "3. 도움말" << endl;
    cout << "4. 게임 종료" << endl;
    
    return get_valid_input(1, 4, "Enter your choice: ");
}

GameState new_game() {
    cout << "=== 새 게임 시작 ===" << endl;
    
    GameCharacter newCharacter;
    
    while (true) {
        cout << "\n1. 직업 선택" << endl;
        cout << "2. 캐릭터 커스터마이즈" << endl;
        cout << "3. 게임 시작" << endl;
        cout << "4. 뒤로 가기" << endl;
        
        int choice = get_valid_input(1, 4, "Enter your choice: ");
        
        switch(choice) {
            case 1: {
                cout << "\n=== 직업 선택 ===" << endl;
                cout << "1. 광부 (높은 체력과 방어력)" << endl;
                cout << "2. 교주 (높은 마나와 지능)" << endl;
                cout << "3. 해커 (높은 민첩성)" << endl;
                cout << "4. 의사 (높은 회복력)" << endl;
                cout << "5. 연설가 (높은 매력)" << endl;
                cout << "6. 암살자 (높은 기민함)" << endl;

                int jobChoice = get_valid_input(1, 6, "직업을 선택하세요: ");

                switch(jobChoice) {
                    case 1:
                        newCharacter.job = "광부";
                        newCharacter.stats = {100, 30, 80, 70, 50, 40};
                        break;
                    case 2:
                        newCharacter.job = "교주";
                        newCharacter.stats = {60, 100, 40, 30, 60, 90};
                        break;
                    case 3:
                        newCharacter.job = "해커";
                        newCharacter.stats = {80, 50, 60, 50, 90, 60};
                        break;
                    case 4:
                        newCharacter.job = "의사";
                        newCharacter.stats = {100, 30, 80, 70, 50, 40};
                        break;
                    case 5:
                        newCharacter.job = "연설가";
                        newCharacter.stats = {60, 100, 40, 30, 60, 90};
                        break;
                    case 6:
                        newCharacter.job = "암살자";
                        newCharacter.stats = {80, 50, 60, 50, 90, 60};
                        break;
                }
                cout << newCharacter.job << "를 선택했습니다!" << endl;
                break;
            }
            case 2:
                if (newCharacter.job.empty()) {
                    cout << "먼저 직업을 선택해주세요!" << endl;
                } else {
                    customize_character(newCharacter);
                }
                break;
            case 3:
                if (newCharacter.job.empty() || newCharacter.name.empty()) {
                    cout << "직업 선택과 캐릭터 커스터마이즈를 먼저 완료해주세요!" << endl;
                } else {
                    cout << "\n캐릭터 생성이 완료되었습니다!" << endl;
                    cout << "이름: " << newCharacter.name << endl;
                    cout << "직업: " << newCharacter.job << endl;
                    cout << "게임을 시작합니다..." << endl;
                    return PLAY; // 상태를 PLAY로 변경
                }
                break;
            case 4:
                return READY; // 메인 메뉴로 돌아가기
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

void game_play() {
    cout << "\n=== 게임 플레이 ===" << endl;
    cout << "1. 탐색 시작" << endl;
    cout << "2. 인벤토리 확인" << endl;
    cout << "3. 상태 확인" << endl;
    cout << "4. 게임 종료" << endl;
    
    int choice = get_valid_input(1, 4, "선택하세요: ");
    
    switch(choice) {
        case 1:
            game_map(); // 던전 맵 함수 호출
            break;
        case 2:
            cout << "인벤토리 기능은 아직 구현되지 않았습니다." << endl;
            break;
        case 3:
            cout << "상태 확인 기능은 아직 구현되지 않았습니다." << endl;
            break;
        case 4:
            cout << "게임을 종료합니다." << endl;
            break;
        default:
            cout << "잘못된 선택입니다." << endl;
            break;
    }
}
