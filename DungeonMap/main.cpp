#include <iostream>
#include <vector>
#include <array>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::array;

enum GameState {
    READY,
    PLAY,
    EXIT
};

struct GameCharacter {
    string name;
    string job;
    array<int, 6> stats; // HP, MP, STR, DEF, AGI, INT
};

int start_game_ui(int choice);
GameState new_game();
void load_game();
void help();    
void exit_game();
void game_intro();
int get_valid_input(int min, int max, const string& prompt);
void customize_character(GameCharacter& character);


int main() {
    // 한글 출력을 위한 콘솔 코드페이지 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    vector<GameCharacter> player;
    player.resize(30);
    
    GameState gameState = READY;
    int choice = 0;
    
    while (gameState != EXIT) {
        if (gameState == READY) {
            choice = start_game_ui(choice);
            
            switch(choice){
                case 1:
                    gameState = new_game();
                    break;
                case 2:
                    load_game();
                    break;
                case 3:
                    help();
                    break;
                case 4:
                    exit_game();
                    gameState = EXIT;
                    break;
            }
        }
        else if (gameState == PLAY) {
            game_intro();
            // 여기에 실제 게임 플레이 로직이 들어갈 예정
            gameState = EXIT; // 임시로 게임 종료
        }
    }

    cout << "Press Enter to exit...";
    cin.ignore(); // 입력 버퍼 비우기
    cin.get();    // 사용자 입력 대기
    return 0;
}

int start_game_ui(int choice) {
    cout << "-----Dungeon Map Game-----" << endl;
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
                cout << "1. 전사 (높은 체력과 방어력)" << endl;
                cout << "2. 마법사 (높은 마나와 지능)" << endl;
                cout << "3. 도적 (높은 민첩성)" << endl;
                
                int jobChoice = get_valid_input(1, 3, "직업을 선택하세요: ");
                
                switch(jobChoice) {
                    case 1:
                        newCharacter.job = "전사";
                        newCharacter.stats = {100, 30, 80, 70, 50, 40}; // HP, MP, STR, DEF, AGI, INT
                        break;
                    case 2:
                        newCharacter.job = "마법사";
                        newCharacter.stats = {60, 100, 40, 30, 60, 90};
                        break;
                    case 3:
                        newCharacter.job = "도적";
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
                break; //어쩌피 return을 통해 함수가 종료되니까 필요없다고 느낄 수 있지만 if문을 통과하는 경우에 필요하다.
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

void customize_character(GameCharacter& character) {
    cout << "\n=== 캐릭터 커스터마이즈 ===" << endl;
    
    cout << "캐릭터의 이름을 입력하세요: ";
    cin.ignore(); // 입력 버퍼 비우기
    getline(cin, character.name);
    
    cout << "\n현재 스탯:" << endl;
    cout << "HP: " << character.stats[0] << endl;
    cout << "MP: " << character.stats[1] << endl;
    cout << "STR: " << character.stats[2] << endl;
    cout << "DEF: " << character.stats[3] << endl;
    cout << "AGI: " << character.stats[4] << endl;
    cout << "INT: " << character.stats[5] << endl;
    
    cout << "\n추가 스탯 포인트 10점을 배분할 수 있습니다." << endl;
    int remainingPoints = 10;
    
    while (remainingPoints > 0) {
        cout << "\n남은 포인트: " << remainingPoints << endl;
        cout << "1. STR (+1)  2. DEF (+1)  3. AGI (+1)  4. INT (+1)  5. 완료" << endl;
        
        int choice = get_valid_input(1, 5, "어느 스탯을 올리시겠습니까? ");
        
        if (choice == 5) {
            break; 
        } else if (choice >= 1 && choice <= 4) {
            character.stats[choice + 1]++; // STR은 index 2부터 시작
            remainingPoints--;
            cout << "스탯이 증가했습니다!" << endl;
        } 
    }
    
    cout << "\n최종 스탯:" << endl;
    cout << "이름: " << character.name << endl;
    cout << "직업: " << character.job << endl;
    cout << "HP: " << character.stats[0] << endl;
    cout << "MP: " << character.stats[1] << endl;
    cout << "STR: " << character.stats[2] << endl;
    cout << "DEF: " << character.stats[3] << endl;
    cout << "AGI: " << character.stats[4] << endl;
    cout << "INT: " << character.stats[5] << endl;
    
    cout << "\n캐릭터 커스터마이즈가 완료되었습니다!" << endl;
}

// 타입 검사와 범위 검사를 한번에 하는 함수
int get_valid_input(int min, int max, const string& prompt) {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        
        // 타입 검사
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요." << endl;
            continue;
        }
        
        // 범위 검사
        if (input < min || input > max) { //원래는 1 <= input <= 4가 맞는데 if문에서 예외의 경우를 먼저 고려해서 이걸 뒤집으면 input < 1 or input > 4가 된다.
            cout << min << "~" << max << " 사이의 숫자를 입력해주세요." << endl;
            continue;
        }
        
        return input; // 유효한 입력이면 반환
    }
}