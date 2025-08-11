#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string>

using std::vector;
using std::string;

struct MapTile {
    int id;
    string symbol;
    string description;
    bool isAccessible;
};

class GameMap {
private:
    vector<vector<MapTile>> map;
    int playerX, playerY;
    int mapWidth, mapHeight;
    
public:
    GameMap();
    void initializeMap();
    void displayMap();
    void movePlayer(char direction);
    bool isValidMove(int x, int y);
    void setPlayerPosition(int x, int y);
    MapTile* getCurrentTile();
};

// 게임 맵 관련 함수
void game_map();

#endif // GAME_MAP_H
