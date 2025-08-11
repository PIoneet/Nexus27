#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <string>
#include <array>

using std::string;
using std::array;

enum GameState {
    READY,
    PLAY,
    EXIT
};

struct GameCharacter {
    string name;
    string job;
    array<int, 6> stats; // HP, MP, STR, DEF, AGI, INT
};

#endif // GAME_TYPES_H
