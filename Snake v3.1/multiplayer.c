#include "ini.h"
#include "apple.h"
#include "timing.h"
#include "snake.h"
#include "crash.h"
#include "field.h"
#include "windowIni.h"
#include "menu.h"


void multiPlayer(){

    // Minden iras kitorlese a konzolbol
    system("cls");
    srand(time(0));

    // Ablak szelessege es magassaga
    int width = 1030;
    int height = 530;

    // Ablak letrehozas es inicializalas
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(width,height,&window,&renderer);

    // Zene
    /*SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *backgroundSound = Mix_LoadMUS("song.mp3");
    Mix_Chunk *eatingEffect = Mix_LoadWAV("eating.mp3");*/

    // Idozito
    SDL_TimerID id = SDL_AddTimer(120, idozit, NULL);

    // Alap ertekek
    int x1,y1,x2,y2,R;
    // Elso kigyo
    x1=150;
    y1=80;
    // Masodik kigyo
    x2=670;
    y2=80;

    //Atmero
    R=5;

    // Adatok betoltese strukturaba
    snakeBits bits1;
    bits1.x = x1;
    bits1.y = y1;

    snakeBits bits2;
    bits2.x = x2;
    bits2.y = y2;

    // Kigyok hossza
    int length1 = 0;
    int length2 = 0;


    // Lancolt lista feltoltese kezdeti adatokkal (3 pont koordinataja)
    listData* first = NULL;
    length1++;

    listData* second = NULL;
    length2++;

    listAdd(&first,bits1);
    bits1.x += 10;
    length1++;
    listAdd(&first,bits1);
    bits1.x += 10;
    length1++;
    listAdd(&first,bits1);

    listAdd(&second,bits2);
    bits2.x += 10;
    length2++;
    listAdd(&second,bits2);
    bits2.x += 10;
    length2++;
    listAdd(&second,bits2);


    // Palyak letrehozasa
    multiField(renderer);

    // Almak letrehozasa
    applePlace apple1 = createApple(renderer);
    applePlace apple2 = createApplePlus(renderer);

    /*Mix_PlayMusic(backgroundSound,-1);
    Mix_VolumeMusic(4);*/ // Zene inditasa

    snakeDraw(renderer,first,R,0,255,0);
    snakeDraw(renderer,second,R,0,0,255);

    // Kezdeti iranyok
    dirs dir1 = right;
    dirs dir2 = right;

    bool firstCrash = false;
    int score1 = 0;
    bool secondCrash = false;
    int score2 = 0;


    bool quit = false;
    while(!quit){
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_USEREVENT:

                // Utkozesvizsgalat (balos kigyo)
                if(crash(first) || suicide(first)){
                    firstCrash = true;
                    }

                // Utkozesvizsgalat (jobbos kigyo)
                if(crash2(second) || suicide2(second)){
                    secondCrash = true;
                    }

                // Megette az almat (balos kigyo)?
                if(hitIt(apple1, first)){
                    length1++;
                    listAdd(&first,bits1);
                    apple1 = createApple(renderer);
                    /*Mix_PlayChannel(-1, eatingEffect, 0);
                    Mix_VolumeChunk(eatingEffect, 5);*/
                    score1++;
                }

                // Megette az almat (jobbos kigyo)?
                if(hitIt(apple2, second)){
                    length2++;
                    listAdd(&second,bits2);
                    apple2 = createApplePlus(renderer);
                    /*Mix_PlayChannel(-1, eatingEffect, 0);
                    Mix_VolumeChunk(eatingEffect, 5);*/
                    score2++;
                }

                // Ha utkozik a kigyo, ne leptesse tovabb
                if(!firstCrash){
                snakeDraw(renderer,first,R,105,189,210);
                // Lepteto fuggveny
                first = snakePath(first, dir1, R, length1);
                snakeDraw(renderer,first,R,0,255,0);
                }

                if(!secondCrash){
                snakeDraw(renderer,second,R,200,80,80);
                second = snakePath(second, dir2, R, length2);
                snakeDraw(renderer,second,R,0,0,255);
                }

                if(secondCrash && firstCrash){
                    quit = true;
                    SDL_DestroyWindow(window);
                    //Mix_CloseAudio();
                }

                SDL_RenderPresent(renderer);
                break;

            // Billentyulenyomas hatasara valtoztasson iranyt a kigyo
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_a: if(dir1 != right) dir1 = left; break;
                    case SDLK_s: if(dir1 != up) dir1 = down; break;
                    case SDLK_d: if(dir1 != left) dir1 = right; break;
                    case SDLK_w: if(dir1 != down) dir1 = up; break;
                    // Szunet
                    case SDLK_SPACE: SDL_RemoveTimer(id); break;
                    case SDLK_r: SDL_AddTimer(150,idozit,NULL); break;

                    case SDLK_RIGHT: if(dir2 != left) dir2 = right; break;
                    case SDLK_DOWN: if(dir2 != up) dir2 = down; break;
                    case SDLK_LEFT: if(dir2 != right) dir2 = left; break;
                    case SDLK_UP: if(dir2 != down) dir2 = up; break;
                    case SDLK_0: SDL_RemoveTimer(id); break;
                    case SDLK_1: SDL_AddTimer(150,idozit,NULL); break;
                }
                break;

            case SDL_QUIT: quit = true; break;
        }
    }

    SDL_RenderPresent(renderer);

    if(score1 > score2){
        printf("Baloldali jatekos nyert! [%d] : [%d]\n",score1,score2);
    }
    else if(score1 < score2){
        printf("Jobboldali jatekos nyert! [%d] : [%d]\n",score1,score2);
    }
    else{
        printf("Dontetlen! [%d] : [%d]\n",score1,score2);
    }

    int pick = endgameMenu();



    // felszabadito fuggvenyek

    // Lista foglalasanak felszabaditasa
    listData* iter1 = first;
    while(iter1 != NULL){
        listData* mov = iter1->next;
        free(iter1);
        iter1 = mov;
    }

    listData* iter2 = second;
    while(iter2 != NULL){
        listData* mov = iter2->next;
        free(iter2);
        iter2 = mov;
    }


    SDL_RemoveTimer(id);
    /*Mix_FreeChunk(eatingEffect);
    SDL_Quit();
    Mix_CloseAudio();*/


    // Menu vagy kilepes
    if(pick == 1)
        menu();
    if(pick == 2)
        system("cls");
}
