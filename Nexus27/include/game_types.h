#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <string>
#include <array>
#include <utility>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;


enum GameState {
    READY,
    INTRO,
    GAME_PLAY,
    EXIT
};

class MapTile {
public:
    string symbol;
    string color; 
    vector<float> stats; //+(오른쪽) , -(왼쪽), x(윗쪽), /(아랫쪽)
    bool isAccessible;
    pair<int, int> position; //게임 캐릭터의 현재 위치
    //주인공 객체 생성자
    MapTile() 
        : symbol("◆ "), color("white"), stats({1.0, -1.0, 1.0, -1.0}), isAccessible(true), position({4, 4}) {}
    //모든 타일 객체 생성자
    MapTile(string symbol, string color, vector<float> stats, bool isAccessible, pair<int, int> position) 
        : symbol(symbol), color(color), stats(stats), isAccessible(isAccessible), position(position) {}
    //보스 객체 생성자
    MapTile(string color, pair<int, int> position) 
        : symbol("★"), color(color), stats({0, 0, 0, 0}), isAccessible(true), position(position) {}
};


class GameMap: public MapTile {
private:
    vector<vector<MapTile>> map; // vector 하나 둘러싼게 1차원 배열(한줄) 2개 둘러싼게 2차원 배열(여러줄)
    int playerX, playerY; //이거는 플레이어 좌표
    int mapWidth, mapHeight;
    
public:
    GameMap();
    void initializeMap();
    void displayMap(const string& symbol, const string& color);
    void movePlayer(char direction);
    bool isValidMove(int x, int y);
    void setPlayerPosition(int x, int y);
    int getPlayerX();
    int getPlayerY();
    MapTile* getCurrentTile();
    void setTileColor(int x, int y, const std::string& color);
};



class GameCharacter : public MapTile {
public:
    string name;
    int currentPower; //현재 방향 스탯
    int totalPower; //스탯 총합 
    GameMap* opMap; //2명의 player가 참조할 하나의 opMap
    GameCharacter(string name, GameMap* opMap)
        : MapTile(), name(name), currentPower(0), totalPower(0), opMap(opMap) {}
    GameCharacter (GameMap* opMap)
        : MapTile(), name(""), currentPower(0), totalPower(0), opMap(opMap) {}
};

extern GameState gameState;
extern GameMap globalMap;
extern vector<GameCharacter> player;
extern GameCharacter* currentPlayer;

pair<int, int> operation_map(GameCharacter& player);

#endif // GAME_TYPES_H
