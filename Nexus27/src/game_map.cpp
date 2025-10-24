#include "game_types.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "termcolor.hpp"
#include "character.h"

using namespace std;

ostream& setColor(ostream& os, const string& color) {  
    if (color == "red") return termcolor::red(os);
    if (color == "green") return termcolor::green(os);
    if (color == "yellow") return termcolor::yellow(os);
    if (color == "blue") return termcolor::blue(os);
    if (color == "magenta") return termcolor::magenta(os);
    if (color == "cyan") return termcolor::cyan(os);
    if (color == "white") return termcolor::white(os);
    return termcolor::reset(os);
}

void GameMap::initializeMap() {
    // 9x9 그리드 초기화 (빈 공간은 접근 불가능)
    map.resize(mapHeight, vector<MapTile>(mapWidth));
    // 모든 타일을 기본적으로 접근 불가능하게 설정
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            map[i][j] = MapTile("■", "white", random_generate(), false, {i, j}, 0);
        }
    }
    
    // 9x9 다이아몬드 형태 타일 배치
    // 맵 구조:
    //     ###      (3개) - row 0
    //    #####     (5개) - row 1
    //   #######    (7개) - row 2
    //  #########   (9개) - row 3
    //  #########   (9개) - row 4 (중앙)
    //  #########   (9개) - row 5
    //   #######    (7개) - row 6
    //    #####     (5개) - row 7
    //     ###      (3개) - row 8
    // 총 타일: 3+5+7+9+9+9+7+5+3 = 57개
    for (int j = 3; j <= 5; j++) {
        map[0][j].isAccessible = true;
    }
    // Row 1: 5개 타일
    for (int j = 2; j <= 6; j++) {
        map[1][j].isAccessible = true;
    }
    // Row 2: 7개 타일
    for (int j = 1; j <= 7; j++) {
        map[2][j].isAccessible = true;
    }
    // Row 3: 9개 타일 (첫 번째)
    for (int j = 0; j <= 8; j++) {
        map[3][j].isAccessible = true;
    }
    // Row 4: 9개 타일 (중앙)
    for (int j = 0; j <= 8; j++) {
        map[4][j].isAccessible = true;
    }
    // Row 5: 9개 타일 (세 번째)
    for (int j = 0; j <= 8; j++) {
        map[5][j].isAccessible = true;
    }
    // Row 6: 7개 타일
    for (int j = 1; j <= 7; j++) {
        map[6][j].isAccessible = true;
    }
    // Row 7: 5개 타일
    for (int j = 2; j <= 6; j++) {
        map[7][j].isAccessible = true;
    }
    // Row 8: 3개 타일
    for (int j = 3; j <= 5; j++) {
        map[8][j].isAccessible = true;
    }
}

void GameMap::displayMap(const vector<GameCharacter>& players) {
    system("cls"); // 화면 지우기
    cout << "=============================== Game Map ===============================" << endl;
    cout << "현재 위치: (" << playerX << ", " << playerY << ")" << endl;
    cout << "\n";
    for (int i = 0; i < mapHeight; i++) {
        bool mapAccess = true;

        cout << "  "; // 들여쓰기
        for (int j = 0; j < mapWidth; j++) {
            if (i == players[0].position.second && j == players[0].position.first) {
                setColor(cout, players[0].color);
                cout << players[0].symbol << termcolor::reset;

            } else if (i == players[1].position.second && j == players[1].position.first) {
                setColor(cout, players[1].color);
                cout << players[1].symbol << termcolor::reset;

            } else if (map[i][j].isAccessible) {
                if (map[i][j].color == "white") {
                    cout << map[i][j].symbol << " ";
                }
                else{
                    setColor(cout, map[i][j].color);
                    cout << map[i][j].symbol << " "<< termcolor::reset;
                }
            } else {
                cout << "  "; // 빈 공간
            }

            

            if(j == mapWidth-1) {
                cout << "      ";
                for(size_t p = 0; p < mapWidth; p++) {
                    if(map[i][p].isAccessible){
                        if(mapAccess){
                            cout << "  ";
                            mapAccess = false;
                        }
                        cout << '?' << " ";
                    }
                    else{
                        cout << "  ";
                    }
                }
            }

            mapAccess = true;
            if(j == mapWidth-1) {
                cout << "      ";
                for(size_t k = 0; k < mapWidth; k++) {
                    if(map[i][k].isAccessible){
                        if(mapAccess){
                            cout << "  ";
                            mapAccess = false;
                        }
                        cout << '0' << " ";
                    }
                    else{
                        cout << "  ";
                    }
                }
            }
        
        }
        cout << endl;
    }

    cout << '\n' << "========================================================================" << endl;
}

void GameMap::movePlayer(GameCharacter& player, char direction) {
    int stateIndex;
    int newX = playerX;
    int newY = playerY;
    
    switch (direction) {
        // x방향
        case 'w':
        case 'W':
            stateIndex = 0;
            //calculatePower(player, stateIndex);
            newY--;
            break;
        // /방향
        case 's':
        case 'S':
            stateIndex = 1;
            //calculatePower(player, stateIndex);
            newY++;
            break;
        // -방향
        case 'a':
        case 'A':
            stateIndex = 2;
            //calculatePower(player, stateIndex);
            newX--;
            break;
        // +방향
        case 'd':
        case 'D':
            stateIndex = 3;
            //calculatePower(player, stateIndex);
            newX++;
            break;
        default:
            cout << "잘못된 입력입니다." << endl;
            return;
    }
    
    if (isValidMove(newX, newY)) {
        setTileColor(playerX, playerY, "green"); // 이전 위치를 녹색으로 변경
        playerX = newX;
        playerY = newY;
        cout << "이동했습니다!" << endl;
    } else {
        cout << "그 방향으로는 갈 수 없습니다!" << endl;
    }
}

void GameMap::movePlayer(GameCharacter& player, int direction) {
    int stateIndex;
    int newX = playerX;
    int newY = playerY;
    switch (direction) {
        //x방향
        case 72:// 위쪽 화살표
            stateIndex = 0;
            //calculatePower(player, stateIndex);
                newY--;
                break;
        // /방향
        case 80:// 아래쪽 화살표
            stateIndex = 1;
            //calculatePower(player, stateIndex);
            newY++;
            break;
        // -방향
        case 75:// 왼쪽 화살표
            stateIndex = 2;
            //calculatePower(player, stateIndex);
            newX--;
            break;
        // + 방향
        case 77:// 오른쪽 화살표
            stateIndex = 3;
            //calculatePower(player, stateIndex);
            newX++;
            break;
        default:
            cout << "잘못된 입력입니다." << endl;
            return;
    }
    
    
    if (isValidMove(newX, newY)) {
        setTileColor(playerX, playerY, "red"); // 이전 위치를 빨간색으로 변경
        
        playerX = newX;
        playerY = newY;

        cout << "이동했습니다!" << endl;
    } else {
        cout << "그 방향으로는 갈 수 없습니다!" << endl;
    }

}



bool GameMap::isValidMove(int x, int y) {
    // 맵 범위 체크
    if ( (x < 0 || x >= mapWidth) || (y < 0 || y >= mapHeight) ) {
        return false;
    }
    
    // 접근 가능한 타일인지 체크
    return map[y][x].isAccessible;
}

void GameMap::setPlayerPosition(int x, int y) {
    if (isValidMove(x, y)) {
        playerX = x;
        playerY = y;
    }
}

int GameMap::getPlayerX(){
    return playerX;
}

int GameMap::getPlayerY(){
    return playerY;
}

MapTile* GameMap::getCurrentTile() {
    return &map[playerY][playerX];
}

void GameMap::setTileColor(int x, int y, const string& color) {
     map[y][x].color = color;
}

//void GameMap::calculatePower(GameCharacter& player, int stateIndex){}

// 1번 플레이어 조작
pair<int, int> GameMap::operation_map(vector<GameCharacter>& players) {

    char input;
    while (true) {
        players[0].opMap->setPlayerPosition(players[0].position.first, players[0].position.second);
        players[0].opMap->displayMap(players);
        cout << "\n1번 플레이어 조작: W(x위쪽), S(/아랫쪽), A(-왼쪽), D(+오른쪽), Q(나가기)" << endl;
        cout << "\n명령을 입력하세요: ";
        cin >> input;
        
        if (input == 'q' || input == 'Q') {
            cout << "탐색을 종료합니다." << endl;
            return {players[0].opMap->getPlayerX(), players[0].opMap->getPlayerY()};
        }

        players[0].opMap->movePlayer(players[0], input);
        players[0].position = {players[0].opMap->getPlayerX(), players[0].opMap->getPlayerY()};
        players[0].opMap->displayMap(players);
        
        //끝나면 바로 다음 플레이어 operation_map 호출
        players[1].tileId = 2;
        players[1].opMap->operation_map(players, players[1].tileId);
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}


void GameMap::operation_map(vector<GameCharacter>& players, int id) {
    int input;
    players[1].opMap->setPlayerPosition(players[1].position.first, players[1].position.second);
    players[1].opMap->displayMap(players);
    // 조작 설명을 여기로 옮기는게 나을 것 같기도 하고
    cout << "\n2번 플레이어 조작: ↑(x위쪽), ↓(/아랫쪽), ←(-왼쪽), →(+오른쪽)" << endl;
    while(true){
        cout << "\n명령을 입력하세요: ";
        input = _getch();
        if(input == 224) { // 특수 키(화살4표 키 등)의 경우
            input = _getch(); // 실제 키 코드 읽기
        }
        players[1].opMap->movePlayer(players[1], input);
        if(input == 72 || input == 80 || input == 75 || input == 77) break;
    }

    players[1].position = {players[1].opMap->getPlayerX(), players[1].opMap->getPlayerY()};
    players[1].opMap->displayMap(players);
}
