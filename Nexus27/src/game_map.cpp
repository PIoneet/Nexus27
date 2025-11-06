#include "game_types.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "termcolor.hpp"
#include "character.h"
#include "input_utils.h"

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
            map[i][j] = MapTile("■", "white", random_generate(), false, {i, j});
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

void GameMap::displayMap(vector<GameCharacter>& players, string color) {
    system("cls"); // 화면 지우기

    initializeOccupiedTiles(players);
    cout << "=============================== Game Map ===============================" << endl;
    cout << "플레이어 현재 전력: "; 
    setColor(cout, color);
    cout << map[playerY][playerX].power << "명" << termcolor::reset << endl;
    cout << "\n";
    for (int i = 0; i < mapHeight; i++) {
        bool mapAccess = true;

        cout << "  "; // 들여쓰기
        for (int j = 0; j < mapWidth; j++) {
            if (i == players[0].position.second && j == players[0].position.first) {
                setColor(cout, players[0].color);
                map[i][j].color = players[0].color;
                cout << players[0].symbol << termcolor::reset;

            } else if (i == players[1].position.second && j == players[1].position.first) {
                setColor(cout, players[1].color);
                map[i][j].color = players[1].color;
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
                        if(map[i][p].color != "white" || i == players[0].position.second && p == players[0].position.first || i == players[1].position.second && p == players[1].position.first){
                            setColor(cout, map[i][p].color);
                            cout << map[i][p].power << " "<< termcolor::reset;
                        }else
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
                        cout << 'x' << " ";
                    }
                    else{
                        cout << "  ";
                    }
                }
            }
            // 점령 지역 계산
            if(map[i][j].color == players[0].color)
                players[0].occupiedTiles += 1;
            else if(map[i][j].color == players[1].color)
                players[1].occupiedTiles += 1;
            
            
            
        }
        cout << endl;
        // 이 함수에서 따로 전투력 계산해주는 ui 출력해도 좋을듯. 함수 호출을 여기서 하는거지
    }

    string space = "       ";
    cout << "\n                       "; 
    setColor(cout, players[0].color); 
    cout<< players[0].occupiedTiles << "타일" << termcolor::reset;
    cout << space << "vs" << space;
    setColor(cout, players[1].color);
    cout<< players[1].occupiedTiles << "타일" << termcolor::reset;

    if(players[0].occupiedTiles > players[1].occupiedTiles)
        players[0].turn = true;
    else if(players[0].occupiedTiles < players[1].occupiedTiles)
        players[0].turn = false;

    cout << '\n' << '\n' << "========================================================================" << endl;
}

void GameMap::movePlayer(GameCharacter& player, char& direction) {
    int stateIndex;

    cout << "\n1번 플레이어 조작: W(x위쪽), S(/아랫쪽), A(-왼쪽), D(+오른쪽), Q(나가기)" << endl;
    
    while(true){
        int newX = playerX;
        int newY = playerY;
        cout << "\n명령을 입력하세요: ";
        cin >> direction;

        if (direction == 'q' || direction == 'Q') {
            cout << "탐색을 종료합니다." << endl;
            return;
        }
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
                continue;
        }

        if (isValidMove(newX, newY)) {
            setTileColor(playerX, playerY, player.color);

            if(map[newY][newX].color == player.color){
                swap_int(getCurrentTile()->power, map[newY][newX].power);    
            }
            
            playerX = newX;
            playerY = newY;
            

            cout << "이동했습니다!" << endl;
            break;
        } else {
            cout << "그 방향으로는 갈 수 없습니다!" << endl;
        }

        cout << "\nPress Enter to continue..."; 
        cin.ignore();
        cin.get();
    }
}

void GameMap::movePlayer(GameCharacter& player, int direction) {
    int stateIndex;
    cout << "\n2번 플레이어 조작: ↑(x위쪽), ↓(/아랫쪽), ←(-왼쪽), →(+오른쪽)" << endl;
    
    while(true){
        int newX = playerX;
        int newY = playerY;

        cout << "\n명령을 입력하세요: ";
        direction = _getch();
        if(direction == 224) { // 특수 키(화살4표 키 등)의 경우
            direction = _getch(); // 실제 키 코드 읽기
        }    

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
                continue;
        }
    
    
        if (isValidMove(newX, newY)) {
            setTileColor(playerX, playerY, player.color);
            playerX = newX;
            playerY = newY;

            cout << "이동했습니다!" << endl;
            break;
        } else {
            cout << "그 방향으로는 갈 수 없습니다!" << endl;
        }
        
        cout << "\nPress Enter to continue..."; 
        cin.ignore();
        cin.get();
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

void GameMap::initializeOccupiedTiles(vector<GameCharacter>& players){
    for(auto& player : players){
        player.occupiedTiles = 0;
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


void GameMap::mapTurn(vector<GameCharacter>& players){
    //1 -> 2
    while(true){
       if(players[0].occupiedTiles > players[1].occupiedTiles || players[0].turn){
            first_map(players);
            second_map(players);
            return;
       } 
       else{
            second_map(players);
            first_map(players);
            return;
       }
    }

}

// 1번 플레이어 조작
void GameMap::first_map(vector<GameCharacter>& players) {

    char direction;
    while (true) {
        players[0].opMap->setPlayerPosition(players[0].position.first, players[0].position.second);
        players[0].opMap->displayMap(players, players[0].color);

        players[0].opMap->movePlayer(players[0], direction);
        /*if (direction == 'q' || direction == 'Q'){
            players[0].position = {players[0].opMap->getPlayerX(), players[0].opMap->getPlayerY()};
            gameState = INTRO;
            return;
        }*/
        players[0].position = {players[0].opMap->getPlayerX(), players[0].opMap->getPlayerY()};
            if(getCurrentTile()->color == players[0].color)
                continue;
        players[0].opMap->displayMap(players, players[0].color);

        cout << "\nPress Enter to continue..."; 
        cin.ignore();
        cin.get();

        break;
    }
}


void GameMap::second_map(vector<GameCharacter>& players) {
    int input;
    
    while(true){

        players[1].opMap->setPlayerPosition(players[1].position.first, players[1].position.second);
        players[1].opMap->displayMap(players, players[1].color);
        players[1].opMap->movePlayer(players[1], input);
        players[1].position = {players[1].opMap->getPlayerX(), players[1].opMap->getPlayerY()};
        
        if(getCurrentTile()->color == players[1].color){
            continue;
        }
        players[1].opMap->displayMap(players, players[1].color);
        
        cout << "\nPress Enter to continue...";
        _getch(); //어쩌피 버퍼에 남아있는거 없으니까 한번만 입력받고 종료

        break;
    }

}
