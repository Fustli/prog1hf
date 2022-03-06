#ifndef INI_H_INCLUDED
#define INI_H_INCLUDED
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include "debugmalloc.h"

typedef enum pick{
    singleplayer = 1,
    multiplayer = 2,
    record = 3,
    exitGame = 4
}pick;

typedef struct snakeBits{
    int x,y;
}snakeBits;

typedef struct listData{
    snakeBits snakePos;
    struct listData* next;
}listData;

typedef enum dirs{  // Iranyok
    left = 0,
    down = 1,
    right = 2,
    up = 3
}dirs;

typedef struct applePlace{
    int x,y;
}applePlace;





#endif // INI_H_INCLUDED
