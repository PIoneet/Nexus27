#include "../include/game_map.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

GameMap::GameMap() : playerX(5), playerY(4), mapWidth(11), mapHeight(9) {
    initializeMap();
}

void GameMap::initializeMap() {
    // 11x11 그리드 초기화 (빈 공간은 접근 불가능)
    map.resize(mapHeight, vector<MapTile>(mapWidth));
    
    // 모든 타일을 기본적으로 접근 불가능하게 설정
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            map[i][j] = {0, " ", "빈 공간", false};
        }
    }
    
    // 다이아몬드 형태로 57개 타일 배치
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
    for (int j = 4; j <= 6; j++) {
        map[0][j] = {tileId++, "■", "던전 입구", true};
    }
    
    // Row 1: 5개 타일
    for (int j = 3; j <= 7; j++) {
        map[1][j] = {tileId++, "■", "던전 통로", true};
    }
    
    // Row 2: 7개 타일
    for (int j = 2; j <= 8; j++) {
        map[2][j] = {tileId++, "■", "던전 방", true};
    }
    
    // Row 3: 9개 타일 (첫 번째)
    for (int j = 1; j <= 9; j++) {
        map[3][j] = {tileId++, "■", "던전 상층부", true};
    }
    
    // Row 4: 9개 타일 (중앙)
    for (int j = 1; j <= 9; j++) {
        map[4][j] = {tileId++, "■", "던전 중앙부", true};
    }
    
    // Row 5: 9개 타일 (세 번째)
    for (int j = 1; j <= 9; j++) {
        map[5][j] = {tileId++, "■", "던전 하층부", true};
    }
    
    // Row 6: 7개 타일
    for (int j = 2; j <= 8; j++) {
        map[6][j] = {tileId++, "■", "던전 방", true};
    }
    
    // Row 7: 5개 타일
    for (int j = 3; j <= 7; j++) {
        map[7][j] = {tileId++, "■", "던전 통로", true};
    }
    
    // Row 8: 3개 타일
    for (int j = 4; j <= 6; j++) {
        map[8][j] = {tileId++, "■", "던전 출구", true};
    }
    
    // 플레이어 시작 위치 (중앙)
    setPlayerPosition(5, 4); // 가로 중앙, 세로 중앙
}

void GameMap::displayMap() {
    cout << "\n========== 던전 맵 ==========" << endl;
    cout << "플레이어 위치: (" << playerX << ", " << playerY << ")" << endl;
    cout << "현재 위치: " << getCurrentTile()->description << endl;
    cout << "\n";
    
    for (int i = 0; i < mapHeight; i++) {
        cout << "  "; // 들여쓰기
        for (int j = 0; j < mapWidth; j++) {
            if (i == playerY && j == playerX) {
                cout << "◆ "; // 플레이어 위치
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
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
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

MapTile* GameMap::getCurrentTile() {
    return &map[playerY][playerX];
}

void game_map() {
    cout << "\n=== 던전 맵 탐험 ===" << endl;
    cout << "57개의 타일로 구성된 다이아몬드 형태의 던전입니다." << endl;
    
    GameMap dungeonMap;
    char input;
    
    while (true) {
        dungeonMap.displayMap();
        
        cout << "\n명령을 입력하세요: ";
        cin >> input;
        
        if (input == 'q' || input == 'Q') {
            cout << "던전 탐험을 종료합니다." << endl;
            break;
        }
        
        dungeonMap.movePlayer(input);
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
