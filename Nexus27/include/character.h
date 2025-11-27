#ifndef CHARACTER_H
#define CHARACTER_H

#include "game_types.h"

#define COLOR_SIZE 6
// 캐릭터 관련 함수들
void customize_character(vector<GameCharacter>& characters);
int random_generate(pair<int, int> range);
pair<int, int> random_generate_color(int size);
                
#endif // CHARACTER_H
