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
            vector<float> random_stats = random_generate(4);
            map[i][j] = MapTile("■", "white", random_stats, false, {i, j}, 0); //여기서 모든 타일에 random 타일.
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

void GameMap::displayMap(const GameCharacter& player) {
    system("cls"); // 화면 지우기
    cout << "================ Operation Map ================" << endl;
    cout << "현재 위치: (" << playerX << ", " << playerY << ")" << endl;
    cout << "\n";
    for (int i = 0; i < mapHeight; i++) {
        cout << "  "; // 들여쓰기
        for (int j = 0; j < mapWidth; j++) {
            if (i == ::player[0].position.second && j == ::player[0].position.first) {
                setColor(cout, ::player[0].color);
                cout << ::player[0].symbol << termcolor::reset;

            } else if (i == ::player[1].position.second && j == ::player[1].position.first) {
                setColor(cout, ::player[1].color);
                cout << ::player[1].symbol << termcolor::reset;
                
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
        }
        cout << endl;
    }
    
    cout << "==============================================" << endl;
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
            calculatePower(player, stateIndex);
            newY--;
            break;
        // /방향
        case 's':
        case 'S':
            stateIndex = 1;
            calculatePower(player, stateIndex);
            newY++;
            break;
        // -방향
        case 'a':
        case 'A':
            stateIndex = 2;
            calculatePower(player, stateIndex);
            newX--;
            break;
        // +방향
        case 'd':
        case 'D':
            stateIndex = 3;
            calculatePower(player, stateIndex);
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
            calculatePower(player, stateIndex);
                newY--;
                break;
        // /방향
        case 80:// 아래쪽 화살표
            stateIndex = 1;
            calculatePower(player, stateIndex);
            newY++;
            break;
        // -방향
        case 75:// 왼쪽 화살표
            stateIndex = 2;
            calculatePower(player, stateIndex);
            newX--;
            break;
        // + 방향
        case 77:// 오른쪽 화살표
            stateIndex = 3;
            calculatePower(player, stateIndex);
            newX++;
            break;
        default:
            cout << "잘못된 입력입니다." << endl;
            return;
    }
    
    
    if (isValidMove(newX, newY)) {
        setTileColor(playerX, playerY, "red"); // 이전 위치를 빨간색으로 변경
        displayMap(player);
        
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

void GameMap::calculatePower(GameCharacter& player, int stateIndex){
    
    if(stateIndex == 0){
        player.currentPower = player.stats[stateIndex]; //x(윗쪽)
        cout << "현재 x(곱하기) 전투력: " << player.currentPower << endl;
    }
    else if(stateIndex == 1){
        player.currentPower = player.stats[stateIndex]; // /(아랫쪽)
        cout << "현재 /(나누기) 전투력: " << player.currentPower << endl;
    }
    else if(stateIndex == 2){
        player.currentPower = player.stats[stateIndex]; // -(왼쪽)
        cout << "현재 -(마이너스) 전투력: " << player.currentPower << endl;
    }
    else if(stateIndex == 3){
        player.currentPower = player.stats[stateIndex]; // +(오른쪽)
        cout << "현재 +(플러스) 전투력: " << player.currentPower << endl;
    }
}

// 1번 플레이어 조작
pair<int, int> GameMap::operation_map(GameCharacter& player) {

    char input;
    player.tileId = 1;
    while (true) {
        player.opMap->setPlayerPosition(player.position.first, player.position.second);
        player.opMap->displayMap(player);
        cout << "\n1번 플레이어 조작: W(x위쪽), S(/아랫쪽), A(-왼쪽), D(+오른쪽), Q(나가기)" << endl;
        cout << "\n명령을 입력하세요: ";
        cin >> input;
        
        if (input == 'q' || input == 'Q') {
            cout << "탐색을 종료합니다." << endl;
            return {player.opMap->getPlayerX(), player.opMap->getPlayerY()};
        }

        player.opMap->movePlayer(player, input);
        player.position = {player.opMap->getPlayerX(), player.opMap->getPlayerY()};
        player.opMap->displayMap(player);
        
        //끝나면 바로 다음 플레이어 operation_map 호출
        ::player[1].tileId = 2;
        player.opMap->operation_map(::player[1], ::player[1].tileId);
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}


void GameMap::operation_map(GameCharacter& player, int id) {

    player.opMap->setPlayerPosition(player.position.first, player.position.second);
    player.opMap->displayMap(player);
    // 조작 설명을 여기로 옮기는게 나을 것 같기도 하고

    cout << "\n2번 플레이어 조작: ↑(x위쪽), ↓(/아랫쪽), ←(-왼쪽), →(+오른쪽)" << endl;
    cout << "\n명령을 입력하세요: ";
    int input = _getch();
    if(input == 224) { // 특수 키(화살4표 키 등)의 경우
        input = _getch(); // 실제 키 코드 읽기
    }

    player.opMap->movePlayer(player, input);
    player.position = {player.opMap->getPlayerX(), player.opMap->getPlayerY()};
    player.opMap->displayMap(player);
}
