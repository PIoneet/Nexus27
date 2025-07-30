#include <iostream>
#include <vector>
#include <array>

using namespace std;

void game_intro();
int start_game_ui(int choice);
void new_game();

struct GameCharacter {
    string name;
    string job;
    array<int, 6> state;
};

int main() {
    vector<GameCharacter> player;
    player.resize(30);
    
    int exitProgram = 1;
    int choice = 0;
    choice = start_game_ui(choice);

    switch(choice){
        case 0:
            new_game();
            break;
        default:
            exitProgram = 0;
    }

    game_intro();
    if (exitProgram != 0)
        cin.get();
    return 0;
}
int start_game_ui(int choice) {
    cout << "-----Dungeon Map Game-----" << endl;
    cout << "1. 새 게임" << endl;
    cout << "2. 불러오기" << endl;
    cout << "3. 도움말" << endl;
    cout << "4. 게임 종료" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void new_game() {
    cout << "1. 직업 선택" << endl;
    cout << "2. 캐릭터 커스터마이즈" << endl;
    cout << "3. 뒤로 가기" << endl;
    return;
}
void game_intro() {
    cout << "Welcome to our World called Menzo " << endl;
    //대사 넘어갈떄마다 음성 소리 나오는 것도 재밌을듯.
    cout << "" << endl;
    return;
}