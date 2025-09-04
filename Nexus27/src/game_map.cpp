#include "../include/game_map.h"
#include "../include/game_types.h"
#include <iostream>
#include <iomanip>
#include "../include/termcolor.hpp"

using namespace std;

// 문자열로 색상을 지정하는 함수
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


GameMap::GameMap() : playerX(4), playerY(4), mapWidth(9), mapHeight(9) {
    initializeMap();
}

void GameMap::initializeMap() {
    // 9x9 그리드 초기화 (빈 공간은 접근 불가능)
    map.resize(mapHeight, vector<MapTile>(mapWidth));
    
    // 모든 타일을 기본적으로 접근 불가능하게 설정
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            map[i][j] = {0, " ", "빈 공간", "white", false };
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

    int tileId = 1;
    // Row 0: 3개 타일 (중앙에 배치)
    for (int j = 3; j <= 5; j++) {
        map[0][j] = {tileId++, "■", "던전 입구", "white", true};
    }
    // Row 1: 5개 타일
    for (int j = 2; j <= 6; j++) {
        map[1][j] = {tileId++, "■", "던전 통로", "white", true};
    }
    // Row 2: 7개 타일
    for (int j = 1; j <= 7; j++) {
        map[2][j] = {tileId++, "■", "던전 방", "white", true};
    }
    // Row 3: 9개 타일 (첫 번째)
    for (int j = 0; j <= 8; j++) {
        map[3][j] = {tileId++, "■", "던전 상층부", "white", true};
    }
    // Row 4: 9개 타일 (중앙)
    for (int j = 0; j <= 8; j++) {
        map[4][j] = {tileId++, "■", "던전 중앙부", "white", true};
    }
    // Row 5: 9개 타일 (세 번째)
    for (int j = 0; j <= 8; j++) {
        map[5][j] = {tileId++, "■", "던전 하층부", "white", true};
    }
    // Row 6: 7개 타일
    for (int j = 1; j <= 7; j++) {
        map[6][j] = {tileId++, "■", "던전 방", "white", true};
    }
    // Row 7: 5개 타일
    for (int j = 2; j <= 6; j++) {
        map[7][j] = {tileId++, "■", "던전 통로", "white", true};
    }
    // Row 8: 3개 타일
    for (int j = 3; j <= 5; j++) {
        map[8][j] = {tileId++, "■", "던전 출구", "white", true};
    }
    // 플레이어 시작 위치 (중앙)
    setPlayerPosition(4, 4); // 가로 중앙, 세로 중앙
}

void GameMap::displayMap(string& color){
    system("cls"); // 화면 지우기
    cout << "========== Operation Map ==========" << endl;
    cout << termcolor::red << "Hello, ";     
    cout << termcolor::reset;              // 16 colors
    cout << termcolor::color<40> << "Colorful ";          // 256 colors
    cout << termcolor::color<50, 54, 10> << "World!"; 
    cout << termcolor::reset;
    cout << "현재 위치: (" << playerX << ", " << playerY << ")" << endl;
    cout << "특이사항: " << getCurrentTile()->description << endl;
    cout << "\n";
    for (int i = 0; i < mapHeight; i++) {
        cout << "  "; // 들여쓰기
        for (int j = 0; j < mapWidth; j++) {
                if (i == playerY && j == playerX) {
                    // 문자열로 색상 지정하여 플레이어 위치 출력
                    setColor(cout, color);
                    cout << "◆ " << termcolor::reset;
            } else if (map[i][j].isAccessible) {
                cout << map[i][j].symbol << " ";
            } else {
                cout << "  "; // 빈 공간
            }
        }
        cout << endl;
    }
    cout << "\n조작: W(위), A(왼쪽), S(아래), D(오른쪽), Q(나가기)" << endl;
    cout << "==============================" << endl;
}

void GameMap::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;
    
    switch (direction) {
        case 'w':
        case 'W':
            newY--;
            break;
        case 's':
        case 'S':
            newY++;
            break;
        case 'a':
        case 'A':
            newX--;
            break;
        case 'd':
        case 'D':
            newX++;
            break;
        default:
            cout << "잘못된 입력입니다." << endl;
            return;
    }
    
    if (isValidMove(newX, newY)) {
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

MapTile* GameMap::getCurrentTile() { // 82줄에서 단순히 출력 목적이라 MapTile 반환도 가능은하다.
    return &map[playerY][playerX];
}

void GameMap::setTileColor(int x, int y, const string& color) {
     map[x][y].color = color;
}


void GameMap::setPlayerTileColor(int x, int y, const string& color) {
    setTileColor(x, y, color);
}


pair<int, int> operation_map(GameCharacter& player) {

    char input;
    player.opMap->setPlayerTileColor(player.pos.first, player.pos.second, player.color);
    player.opMap->setPlayerPosition(player.pos.first, player.pos.second);
    
    while (true) {
        
        player.opMap->displayMap(player.color);

        cout << "\n명령을 입력하세요: ";
        cin >> input;
        
        if (input == 'q' || input == 'Q') {
            cout << "탐색을 종료합니다." << endl;
            return {player.opMap->getPlayerX(), player.opMap->getPlayerY()};
        }

        player.opMap->movePlayer(input);

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
