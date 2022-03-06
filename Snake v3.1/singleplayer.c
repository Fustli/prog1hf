#include "ini.h"
#include "apple.h"
#include "timing.h"
#include "snake.h"
#include "crash.h"
#include "field.h"
#include "windowIni.h"
#include "menu.h"


void singlePlayer(){
    srand(time(0));

    int width = 1030;
    int height = 530;

    SDL_Window *window;
    SDL_Renderer *renderer;


    system("cls");  // Minden iras kitorlese a konzolbol
    char player[6+1];
    printf("Jatekosnev (6 karakter): ");
    scanf("%s",&player);
    system("cls");
    printf("Jatekban: %s",player);
    sdl_init(width,height,&window,&renderer);   // Ablak és megjelenito inicializalasa

     //Zene
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *backgroundSound = Mix_LoadMUS("song.mp3");
    Mix_Chunk *deathEffect = Mix_LoadWAV("death.mp3");
    Mix_Chunk *eatingEffect = Mix_LoadWAV("eating.mp3");


    // Datum
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Fajl megnyitasa (irashoz)
    FILE *fp;
    fp = fopen("records.txt","at");
    if(fp == NULL){
        perror("Fajl megnyitasa sikertelen");
    }



    // Idozito
    SDL_TimerID id = SDL_AddTimer(120, idozit, NULL);



    // Alap ertekek
    int x,y,R;
    x=150;
    y=80;
    R=5;

    snakeBits bits;
    bits.x = x;
    bits.y = y;


    int score = 0;
    int length = 0;

    // Lista elso feltoltese
    listData* first = NULL;
    length++;

    listAdd(&first,bits);
    bits.x += 20;
    length++;
    listAdd(&first,bits);
    bits.x += 20;
    length++;
    listAdd(&first,bits);

    // Palya letrehozasa
    field(renderer);
    applePlace apple = createApple(renderer);
    // Zene inditasa
    Mix_PlayMusic(backgroundSound,-1);
    Mix_VolumeMusic(4);

    snakeDraw(renderer,first,R,0,255,0);
    dirs dir = right;
    bool quit = false;

    while(!quit){
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_USEREVENT:
                // Megette az almat?
                if(hitIt(apple,first)){
                    score++;
                    length++;
                    // Ha elerte az almat uj elem hozzafuzese a listahoz
                    listAdd(&first,bits);
                    apple = createApple(renderer);
                    Mix_PlayChannel(-1, eatingEffect, 0);
                    Mix_VolumeChunk(eatingEffect, 5);
                }

                 // Utkozesvizsgalat
                if(crash(first) || suicide(first)){
                    system("cls");
                    printf("Jatek veget ert.");
                    //Mix_CloseAudio();
                    quit = true;
                    SDL_DestroyWindow(window);
                    break;
                    }

                snakeDraw(renderer,first,R,105,189,210);
                first = snakePath(first, dir, R, length);
                // Kigyo leptetese "dir" iranyba
                snakeDraw(renderer,first,R,0,255,0);
                SDL_RenderPresent(renderer);
                break;

            // Billentyulenyomas hatasara valtoztasson iranyt a kigyo
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_a: if(dir != right) dir = left; break;
                    case SDLK_s: if(dir != up) dir = down; break;
                    case SDLK_d: if(dir != left) dir = right; break;
                    case SDLK_w: if(dir != down) dir = up; break;
                    case SDLK_SPACE: SDL_RemoveTimer(id);  break;
                    case SDLK_r: SDL_AddTimer(150,idozit,NULL); break;
                }
                break;

            case SDL_QUIT: quit = true; break;
        }
    }

    SDL_RenderPresent(renderer);

    printf("\nElert eredmenyed: %d pont\n",score);
    // Eredmeny fajlba irasa
    fprintf(fp,"%s %d/%d/%d Score: %d\n", player, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, score);

    int pick = endgameMenu();

    if(pick == 2){
        system("cls");
    }


    // Felszabadito fuggvenyek

    // Lista felszabaditasa
    listData* iter = first;
    while(iter != NULL){
        listData* mov = iter->next;
        free(iter);
        iter = mov;
    }



    SDL_RemoveTimer(id);
    Mix_FreeChunk(deathEffect);
    Mix_FreeChunk(eatingEffect);
    SDL_Quit();
    Mix_CloseAudio();
    fclose(fp);

    // Menube leptetes
    if(pick == 1){
        system("cls");
        menu();
    }

}
