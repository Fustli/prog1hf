#include "ini.h"

void field(SDL_Renderer* renderer){ // Letrehozza a palyat
    boxRGBA(renderer, 30, 30, 500, 500, 200,0,0,255);
    boxRGBA(renderer, 40, 40, 490, 490, 105,189,210,255);
}

void multiField(SDL_Renderer* renderer){ // Letrehozza a masik palyat (tobbjatekos)
    boxRGBA(renderer, 30, 30, 500, 500, 200,0,0,255);
    boxRGBA(renderer, 40, 40, 490, 490, 105,189,210,255);
    boxRGBA(renderer, 530, 30, 1000, 500, 105, 189, 210, 255);
    boxRGBA(renderer, 540, 40, 990, 490, 200, 80, 80, 255);

}
