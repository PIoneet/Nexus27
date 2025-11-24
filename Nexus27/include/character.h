#ifndef CHARACTER_H
#define CHARACTER_H

#include "game_types.h"

#define COLOR_SIZE 2
// 캐릭터 관련 함수들
void customize_character(vector<GameCharacter>& characters, bool& created);
int random_generate(pair<int, int> range);

#endif // CHARACTER_H
