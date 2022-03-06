#include "ini.h"
#include "singleplayer.h"
#include "multiplayer.h"

void menu(){
    int playerpick = 0;
    while(playerpick > 4 || playerpick < 1){    // Addig irja ki a menut amig jo szamot nem valaszott a felhasznalo
    system("cls");
    printf("Egyjatekos mod : [1]");
    printf("\nTobbjatekos mod : [2]");
    printf("\nDicsoseg lista : [3]");
    printf("\nKilepes : [4]\n");
    scanf("\n%d",&playerpick);
    }

    switch(playerpick){
        case singleplayer: singlePlayer(); break;
        case multiplayer: multiPlayer(); break;
        case record:
                system("cls");
                printf("A rekordok a \"records.txt\" fajlban vannak elmentve.\n");
                int pick = endgameMenu();
                if(pick == 1)
                    menu();
                break;
        case exitGame: system("cls"); exit(0); break;
    }
}

int endgameMenu(){                  // Ha veget ert a jatek
    int playerpick = 0;
    while(playerpick>2 || playerpick<1){
    printf("Menu: [1]");
    printf("\nKilepes: [2]\n");
    scanf("%d",&playerpick);
    system("cls");
    }
    return playerpick;
}
