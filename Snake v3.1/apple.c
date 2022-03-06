#include "ini.h"
#include "snake.h"

applePlace createApple(SDL_Renderer* renderer){ // Letrehoz egy almat
    applePlace newA;
    newA.x = (rand()%440)/10*10+50;
    newA.y = (rand()%440)/10*10+50;
    filledCircleRGBA(renderer, newA.x, newA.y, 5, 255, 0, 0, 255);

    return newA;
}

applePlace createApplePlus(SDL_Renderer* renderer){ // Letrehoz egy almat (tobbjatekosban)
    applePlace newB;
    newB.x = (rand()%440)/10*10+550;
    newB.y = (rand()%440)/10*10+50;
    filledCircleRGBA(renderer, newB.x, newB.y, 5, 0, 255, 0, 255);

    return newB;
}


bool hitIt(applePlace apple,listData* first){ // Ellenorzi, hogy a kigyo hozzaert-e az almahoz
    int sx = first->snakePos.x;
    int sy = first->snakePos.y;
    if(apple.x == sx && apple.y == sy)
        return true;
    return false;

}
