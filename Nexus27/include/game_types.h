#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <string>
#include <array>
#include "game_map.h"

using namespace std;

enum GameState {
    READY,
    INTRO,
    GAME_PLAY,
    EXIT
};

struct GameCharacter {
    string name;
    string job;
    array<int, 6> stats; // STR, MEN, TEC, RES, PER, AGI
    GameMap* opMap; //3명의 player가 참조할 하나의 opMap
    string color; // 캐릭터 개인의 색깔(구별 용도)
    pair<int, int> pos; //게임 캐릭터의 현재 위치

    GameCharacter(string name, string job, array<int, 6> stats, GameMap* opMap, string color, pair<int, int> pos)
        : name(name), job(job), stats(stats), opMap(opMap), color(color), pos(pos) {}
        //그니까 매번 opMap 초기화할거면 참조 쓰고 아니면 null 가능한 포인터
        //(객체 생성시 인수로 넣을것들) : (인수 안넣을거면 여기서 미리 초기화)
        //opMap은 포인터 변수를 받겠다는 뜻이다. 
        GameCharacter (GameMap* opMap)
        : name(""), job(""), stats({20,20,20,20,20,20}), opMap(opMap), color(""), pos({4, 4}) {}

        GameCharacter (GameMap* opMap, string color)
        : name(""), job(""), stats({20,20,20,20,20,20}), opMap(opMap), color(color), pos({4, 4}) {}
};

extern GameState gameState;
extern GameMap globalMap;
extern vector<GameCharacter> player;
extern GameCharacter* currentPlayer;

pair<int, int> operation_map(GameCharacter& player);

#endif // GAME_TYPES_H
