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

enum GameScore{
    WIN,
    LOSE,
    DRAW
};

enum class Terrain {
    Open,
    Close
};

class MapTile {
public:
    string symbol;
    string color; 
    int power;
    bool isAccessible;
    pair<int, int> position; //게임 캐릭터의 현재 위치
    Terrain terrain;
    string terrainSymbol;
    //주인공 객체 생성자
    MapTile() 
        : symbol("◆ "), color("red"), power(0), isAccessible(true), position({4, 4}), terrain(Terrain::Close), terrainSymbol("x") {}
    //모든 타일 객체 생성자
    MapTile(string symbol, string color, int power, bool isAccessible, pair<int, int> position, Terrain terrain, string terrainSymbol) 
        : symbol(symbol), color(color), power(power), isAccessible(isAccessible), position(position), terrain(terrain), terrainSymbol(terrainSymbol) {}
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
    void initializeOccupiedTiles(vector<GameCharacter>& players);
    void initializeTotalPower(vector<GameCharacter>& players);
    void initializePlayerPosition(vector<GameCharacter>& players);
    void distributeTerrains(std::vector<std::vector<MapTile>>& map);
    void displayMap(vector<GameCharacter>& players, string color, bool& powerCheck);
    void movePlayer(vector<GameCharacter>& players, char& direction, int id);
    bool isValidMove(int x, int y);
    void setPlayerPosition(int x, int y);
    void setTileColor(int x, int y, const std::string& color);
    void setCurrentPower(vector<GameCharacter>& players);
    int getPlayerX();
    int getPlayerY();
    MapTile* getCurrentTile();
    void move_map(vector<GameCharacter>& players, int& id);
};


class GameCharacter : public MapTile {
public:
    string name;
    int hp;
    int startPower; //초기 전투력
    int currentPower; //현재 타일의 전투력
    int totalPower; //전투력 총합
    int occupiedTiles; //점령한 타일 수
    bool turn; // 현재 턴 여부
    bool gameOver; // 게임 종료 여부
    bool zero_power; // 현재 타일 전투력이 0인지 여부
    GameMap* opMap; //2명의 플레이어가 참조할 하나의 opMap

    GameCharacter (GameMap* opMap)
        : MapTile(), name(""), hp(3), startPower(0), currentPower(0), totalPower(0), occupiedTiles(0), turn(true), gameOver(false) ,zero_power(false), opMap(opMap) {}

};

extern GameState gameState;
extern GameScore gameScore;
extern GameMap globalMap;
extern vector<GameCharacter> player;
extern GameCharacter* currentPlayer;
extern int id;

#endif // GAME_TYPES_H
