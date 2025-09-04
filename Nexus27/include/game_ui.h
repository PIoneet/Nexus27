#ifndef GAME_UI_H
#define GAME_UI_H

#include "game_types.h"
#define COLOR_SIZE 3

// 게임 UI 관련 함수들
int start_game_ui();
GameCharacter* new_game(vector<GameCharacter>& players);
void load_game();
void help();    
void exit_game();
void game_intro();
void game_play(GameCharacter& gamePlayer);



#endif // GAME_UI_H
