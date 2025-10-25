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
    int power;
    bool isAccessible;
    pair<int, int> position; //게임 캐릭터의 현재 위치
    int tileId;
    //주인공 객체 생성자
    MapTile() 
        : symbol("◆ "), color("red"), power(0), isAccessible(true), position({4, 4}), tileId(0) {}
    //모든 타일 객체 생성자
    MapTile(string symbol, string color, int power, bool isAccessible, pair<int, int> position, int tileId) 
        : symbol(symbol), color(color), power(power), isAccessible(isAccessible), position(position), tileId(tileId) {}
};

class GameCharacter; // 전방 선언

class GameMap{

protected:
    vector<vector<MapTile>> map; // vector 하나 둘러싼게 1차원 배열(한줄) 2개 둘러싼게 2차원 배열(여러줄)
    int playerX, playerY; //이거는 플레이어 좌표
    int mapWidth, mapHeight;
    
public:
    GameMap()
        : playerX(4), playerY(4), mapWidth(9), mapHeight(9) 
        {
            initializeMap();
        }
    
    void initializeMap();
    void displayMap(const vector<GameCharacter>& players);
    void movePlayer(GameCharacter& player, char& direction);
    void movePlayer(GameCharacter& player, int direction);
    bool isValidMove(int x, int y);
    void consecutiveMove(int& newX, int& newY);
    void setPlayerPosition(int x, int y);
    int getPlayerX();
    int getPlayerY();
    MapTile* getCurrentTile();
    //void calculatePower(GameCharacter& player, int stateIndex);
    void setTileColor(int x, int y, const std::string& color);
    pair<int, int> operation_map(vector<GameCharacter>& players);
    void operation_map(vector<GameCharacter>& players, int id);
};


class GameCharacter : public MapTile {
public:
    string name;
    int currentPower; //현재 방향 스탯
    int totalPower; //스탯 총합
    GameMap* opMap; //2명의 플레이어가 참조할 하나의 opMap

    GameCharacter (GameMap* opMap)
        : MapTile(), name(""), currentPower(0), totalPower(0), opMap(opMap) {}

};

extern GameState gameState;
extern GameMap globalMap;
extern vector<GameCharacter> player;
extern GameCharacter* currentPlayer;

#endif // GAME_TYPES_H
