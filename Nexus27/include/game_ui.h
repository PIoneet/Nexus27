#ifndef GAME_UI_H
#define GAME_UI_H

#include "game_types.h"

// 게임 UI 관련 함수들
int start_game_ui();
GameState new_game();
void load_game();
void help();    
void exit_game();
void game_intro();
void game_play(); // 게임 플레이 함수 추가

#endif // GAME_UI_H
