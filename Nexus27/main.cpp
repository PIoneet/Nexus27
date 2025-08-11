#include <iostream>
#include <vector>
#include <windows.h>
#include "include/game_types.h"
#include "include/game_ui.h"

using namespace std;

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
                default:
                    cout << "잘못된 선택입니다. 다시 시도하세요." << endl;
                    break;
            }
        }
        else if (gameState == PLAY) {
            game_intro();
            game_play(); // 실제 게임 플레이 함수 호출
            gameState = EXIT; // 게임 플레이 후 종료
        }
    }

    cout << "Press Enter to exit...";
    cin.ignore(); // 입력 버퍼 비우기
    cin.get();    // 사용자 입력 대기
    return 0;
}