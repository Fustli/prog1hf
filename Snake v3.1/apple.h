#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED
#include "ini.h"

applePlace createApple(SDL_Renderer* renderer);
applePlace createApplePlus(SDL_Renderer* renderer);
bool hitIt(applePlace apple,listData* first);




#endif // APPLE_H_INCLUDED
