#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <utility>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

//위 구조체는 1개의 개인 타일을 의미함(단일 객체)
struct MapTile {
    int id;
    string symbol;
    string description;
    string color; // 타일 색깔 멤버 추가
    bool isAccessible;
};

class GameMap { //class라는 설계도를 기반으로 서로 영향받지 않는 복수의 객체들을 만들 수 있음(지도 여러개)
private:
    vector<vector<MapTile>> map; // vector 하나 둘러싼게 1차원 배열(한줄) 2개 둘러싼게 2차원 배열(여러줄)
    int playerX, playerY;
    int mapWidth, mapHeight;
    
public:
    GameMap();
    void initializeMap();
    void displayMap(string& color);
    void movePlayer(char direction);
    bool isValidMove(int x, int y);
    void setPlayerPosition(int x, int y);
    int getPlayerX();
    int getPlayerY();
    MapTile* getCurrentTile();
    void setTileColor(int x, int y, const std::string& color);
    void setPlayerTileColor(int x, int y, const std::string& color);
};



// 게임 맵 관련 함수

#endif // GAME_MAP_H
