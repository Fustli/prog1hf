#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "singleplayer.h"
#include "ini.h"

listData* listAdd (listData* first,snakeBits bits);
void snakeDraw (SDL_Renderer* renderer, listData* first, int R, int r, int g, int b);
listData* snakePath(listData* first, dirs dir, int R, int length);


#endif // SNAKE_H_INCLUDED
