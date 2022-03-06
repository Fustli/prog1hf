#include "ini.h"

// uj elem (kigyoresz) hozzafuzese a listahoz

void listAdd(listData** first,snakeBits bits){
    listData** mov = first;

    while(*mov != NULL)
        mov = &(*mov)->next;

    listData* newData = (listData*) malloc(sizeof(listData));
    newData->snakePos.x = bits.x;
    newData->snakePos.y = bits.y;
    newData->next = NULL;
    *mov = newData;
}

listData* snakePath(listData* first, dirs dir, int R, int length){
    listData* last;
    listData* blast;
    listData* mov;

    mov = first;

    for(int i = 0; i < length-2; i++)
        mov = mov->next;

    blast = mov;
    last = mov->next;
    blast->next = NULL;

    switch(dir){
        case up:    last->snakePos.y = first->snakePos.y - R*2; last->snakePos.x = first->snakePos.x; break;
        case down:  last->snakePos.y = first->snakePos.y + R*2; last->snakePos.x = first->snakePos.x; break;
        case right: last->snakePos.x = first->snakePos.x + R*2; last->snakePos.y = first->snakePos.y; break;
        case left:  last->snakePos.x = first->snakePos.x - R*2; last->snakePos.y = first->snakePos.y; break;
    }
    last->next = first;
    first = last;

    return first;
}

// a kigyo kirajzolasa
void snakeDraw (SDL_Renderer* renderer, listData* first, int R, int r, int g, int b){ // Kirajzol egy kort ami a kigyo lesz
    listData* mov;
    mov = first;
    while(mov != NULL){
        filledCircleRGBA(renderer, mov->snakePos.x, mov->snakePos.y, R, r, g, b, 255);
        mov = mov->next;
    }
}





