#include <iostream>
#include <vector>
#include <windows.h>
#include "include/game_ui.h"
#include "include/game_map.h"
#include "include/character.h"

using namespace std;
GameState gameState = READY; //전역 변수로 설정
GameMap globalMap;
vector<GameCharacter> player(3, GameCharacter(&globalMap));
GameCharacter* currentPlayer = nullptr;

int main() {
    // 한글 출력을 위한 콘솔 코드페이지 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);



    //위 코드로 player 내부에 단일 객체 3개 만들고 생성자로 초기화까지.
    int choice = 0;
    while (gameState != EXIT) {
        if (gameState == READY) {
            choice = start_game_ui();
            
            switch(choice){
                case 1: 
                   currentPlayer = new_game(player);
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
        else if (gameState == INTRO) {
            system("cls"); // 화면 지우기
            game_intro();

            while(gameState == INTRO) {
                game_play(*currentPlayer); // 객체가 필요하니까 *주소값
            }

        }
    }

    cout << "Press Enter to exit...";
    cin.ignore(); // 입력 버퍼 비우기
    cin.get();    // 사용자 입력 대기
    return 0;
}