#include "ini.h"
#include "menu.h"

Uint32 idozit(Uint32 ms, void *param) { // Idozito
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

int main(int argc, char *argv[]) {

    menu();

    return 0;
}
