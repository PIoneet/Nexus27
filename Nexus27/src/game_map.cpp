#include "game_types.h"
#include "game_ui.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include "termcolor.hpp"
#include "character.h"
#include "input_utils.h"
#include <random>    
#include <algorithm>

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
    for (int i = 0; i < mapHeight; i++) { //세로줄 
        for (int j = 0; j < mapWidth; j++) { //가로줄
            map[i][j] = MapTile("■", "white", random_generate(), false, {i, j}, Terrain::Close, ".");
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
    distributeTerrains(map);
}

//Terrain 효과 함수

void GameMap::distributeTerrains(vector<vector<MapTile>>& map) {
    vector<pair<int,int>> coords;
    int h = (int)map.size(); // 행 반환(세로줄)
    int w = (int)map[0].size(); //열 반환(가로줄)

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (map[y][x].isAccessible) coords.emplace_back(x, y);
        }
    }
    int total = (int)coords.size(); // 57 출력

    int base = total / 5; //값이 11

    // terrains 벡터를 섞어서 어느 지형이 잉여를 가지는지 랜덤화
    vector<Terrain> terrains = {Terrain::Close, Terrain::Open};
    random_device rd;
    mt19937 rng(rd());
    vector<Terrain> terrainList;
    terrainList.reserve(total);

    for (int i = 0; i < 2; ++i) {
        for (int k = 0; k < base; ++k) terrainList.push_back(terrains[i]);
        base = total - base;
    }
    std::shuffle(terrainList.begin(), terrainList.end(), rng);

    // 좌표 순서대로 terrainList를 할당
    for (int i = 0; i < total; ++i) {
        int x = coords[i].first;
        int y = coords[i].second;
        map[y][x].terrain = terrainList[i];
        switch (map[y][x].terrain) {
            case Terrain::Close:    map[y][x].terrainSymbol = "x"; break;
            case Terrain::Open:    map[y][x].terrainSymbol = "o"; break;
        }
    }
}

void GameMap::displayMap(vector<GameCharacter>& players, string color) {
    system("cls"); // 화면 지우기

    initializeOccupiedTiles(players);
    initializeTotalPower(players);
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
                        if(map[i][k].color != "white" || i == players[0].position.second && k == players[0].position.first || i == players[1].position.second && k == players[1].position.first){
                            setColor(cout, map[i][k].color);
                            cout << map[i][k].terrainSymbol << " "<< termcolor::reset;
                        }else
                            cout << map[i][k].terrainSymbol << " ";
                    }
                    else{
                        cout << "  ";
                    }
                }
            }
            // 점령 지역 계산
            if(map[i][j].color == players[0].color){
                players[0].totalPower += map[i][j].power; // 플레이어 1의 총 전력
                players[0].occupiedTiles += 1;
            }
            else if(map[i][j].color == players[1].color){
                players[1].totalPower += map[i][j].power; //플레이어 2의 총 전력
                players[1].occupiedTiles += 1;
            }
            
            
            
        }
        cout << endl;
        // 이 함수에서 따로 전투력 계산해주는 ui 출력해도 좋을듯. 함수 호출을 여기서 하는거지
    }

    string space = "       ";
    cout << "\n                       ";
    setColor(cout, players[0].color); 
    cout<< players[0].occupiedTiles << " 타일" << termcolor::reset;
    cout << space << "vs" << space;
    setColor(cout, players[1].color);
    cout<< players[1].occupiedTiles << "타일" << termcolor::reset;
    cout << "\n                       ";

    setColor(cout, players[0].color);
    cout << players[0].totalPower << "명" << termcolor::reset;
    cout << space << "vs" << space;
    setColor(cout, players[1].color);
    cout << players[1].totalPower << "명" << termcolor::reset;

    if(players[0].occupiedTiles > players[1].occupiedTiles)
        players[0].turn = true;
    else if(players[0].occupiedTiles < players[1].occupiedTiles)
        players[0].turn = false;

    cout << '\n' << "========================================================================" << endl;
}

void GameMap::movePlayer(GameCharacter& player, char& direction) {
    cout << "\n1번 플레이어 조작: W(x위쪽), S(/아랫쪽), A(-왼쪽), D(+오른쪽), Q(나가기)" << endl;
    
    while(true){
        if(player.totalPower == player.occupiedTiles && player.totalPower != 0){
            gameState = EXIT;
            return;
        }

        int newX = playerX;
        int newY = playerY;
        cout << "\n명령을 입력하세요: ";
        cin >> direction;

        if (direction == 'q' || direction == 'Q') {
            cout << "탐색을 종료합니다." << endl;
            return;
        }
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
                continue;
        }

        if(map[newY][newX].power == 0){
            player.zero_power = true;
        }
        
        if (isValidMove(newX, newY)) {

            if (map[newY][newX].color == "red"){
                if(getCurrentTile()->power >= map[newY][newX].power && getCurrentTile()->terrainSymbol == map[newY][newX].terrainSymbol){
                    setTileColor(playerX, playerY, player.color);
                    map[newY][newX].power = getCurrentTile()->power - map[newY][newX].power;
                    getCurrentTile()->power = 0;
                    map[newY][newX].color = player.color;
                    playerX = newX;
                    playerY = newY;
                    cout << "\n적의 타일을 점령했습니다!" << endl;
                    continue;
                }
                else{
                    cout << "\n적의 타일을 점령하지 못했습니다!" << endl;
                    continue;
                }
            }
            else {
                if(map[newY][newX].color == player.color) {
                    //0 타일을 밟은 적이 있거나 현 타일이 0이면 병력 교체
                    if(!map[newY][newX].power || !player.zero_power) {
                        swap_int(getCurrentTile()->power, map[newY][newX].power);
                        swap_terrain_symbol(getCurrentTile()->terrainSymbol, map[newY][newX].terrainSymbol);
                    }
                    else
                        {}
                            
                }else{
                    player.zero_power = false;
                    setTileColor(playerX, playerY, player.color);
                }
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
    cout << "\n2번 플레이어 조작: ↑(x위쪽), ↓(/아랫쪽), ←(-왼쪽), →(+오른쪽)" << endl;
    
    while(true){

        if(player.totalPower == player.occupiedTiles && player.totalPower != 0){
            gameState = EXIT;
            return;
        }
        int newX = playerX;
        int newY = playerY;

        cout << "\n명령을 입력하세요: ";
        direction = _getch();
        if(direction == 224) { 
            direction = _getch(); 
        }    

        switch (direction) {
            case 72:
                newY--;
                break;
            case 80:
                newY++;
                break;
            case 75:
                newX--;
                break;
            case 77:
                newX++;
                break;
            default:
                cout << "잘못된 입력입니다." << endl;
                continue;
        }
    
        cout<<'\n';

        if(map[newY][newX].power == 0){
            player.zero_power = true;
        }
    
        if (isValidMove(newX, newY)) {
            
            if (map[newY][newX].color == "green"){
                if(getCurrentTile()->power >= map[newY][newX].power && getCurrentTile()->terrainSymbol == map[newY][newX].terrainSymbol){
                    setTileColor(playerX, playerY, player.color);
                    map[newY][newX].power = getCurrentTile()->power - map[newY][newX].power;
                    getCurrentTile()->power = 0;
                    map[newY][newX].color = player.color;
                    playerX = newX;
                    playerY = newY;
                    cout << "\n적의 타일을 점령했습니다!" << endl;
                    continue;
                }
                else{
                    cout << "\n적의 타일을 점령하지 못했습니다!" << endl;
                    continue;
                }
            }
            else {
                if(map[newY][newX].color == player.color) {
                    //0 타일을 밟은 적이 있거나 현 타일이 0이면 병력 교체
                    if(!map[newY][newX].power || !player.zero_power) {
                        swap_int(getCurrentTile()->power, map[newY][newX].power);
                        swap_terrain_symbol(getCurrentTile()->terrainSymbol, map[newY][newX].terrainSymbol);
                    }
                    else
                        {}
                            
                }else{
                    player.zero_power = false;
                    setTileColor(playerX, playerY, player.color);
                }
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

void GameMap::initializeTotalPower(vector<GameCharacter>& players){
    for(auto& player : players){
        player.totalPower = 0;
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
       if(gameState == EXIT)
            game_play(players);
            
        players[0].position = {players[0].opMap->getPlayerX(), players[0].opMap->getPlayerY()};
            if(getCurrentTile()->color == players[0].color)
                continue;
            if(getCurrentTile()->power == 0)
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

        if(gameState == EXIT)
            game_play(players);
        players[1].position = {players[1].opMap->getPlayerX(), players[1].opMap->getPlayerY()};
        
        if(getCurrentTile()->color == players[1].color)
            continue;
        if(getCurrentTile()->power == 0)
                continue;        
        players[1].opMap->displayMap(players, players[1].color);
        
        cout << "\nPress Enter to continue...";
        _getch(); //어쩌피 버퍼에 남아있는거 없으니까 한번만 입력받고 종료

        break;
    }

}
