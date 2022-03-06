#include "ini.h"
#include "snake.h"

bool crash(listData* first){     // Ellenorzi, hogy utkozott-e a kigyo  fallal
    int x = first->snakePos.x;
    int y = first->snakePos.y;

    if(x >= 490 || x <= 40)
        return true;

    if(y >= 490 || y <= 40)
        return true;

    return false;
}

bool crash2 (listData* first){      // Ellenorzi, hogy utkozott-e a masik kigyo  fallal (tobbjatekos)
    int x = first->snakePos.x;
    int y = first->snakePos.y;

    if(x > 980 || x < 550)
        return true;
    if(y >= 490 || y <= 40)
        return true;

    return false;
}

bool suicide(listData* first){
    listData* mov;
    for(mov = first->next; mov->next != NULL; mov = mov->next){
        if(first->snakePos.x == mov->snakePos.x && first->snakePos.y == mov->snakePos.y)
            return true;
    }
    return false;
}

bool suicide2(listData* first){
    listData* mov;
    for(mov = first->next; mov->next != NULL; mov = mov->next){
        if(first->snakePos.x == mov->snakePos.x && first->snakePos.y == mov->snakePos.y)
            return true;
    }
    return false;
}


