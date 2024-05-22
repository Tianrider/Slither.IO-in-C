#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void firstPageTutorial() {
    // singlePlayer tutorial:
    printf("_____________________________________________________________________________________\n");
    printf(" Gunakan W, A, S, D untuk menggeraakan ular.                           \n");
    printf(" Makan makanan sebanyak mungkin (*) untuk menambahkan panjang ular.    \n");
    printf(" Hindari menabrak dinding dan tubuh ular sendiri.                      \n");
    printf("                       ######################\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #         W          #\n");
    printf("                       #         ^          #\n");
    printf("                       #         |          #\n");
    printf("                       #   W <-  "
           "\033[0;32m"
           "O"
           "\033[0m"
           "  -> D    #\n");
    printf("                       #         |          #\n");
    printf("                       #         v          #\n");
    printf("                       #         S          #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       #                    #\n");
    printf("                       ######################\n");
    printf("_____________________________________________________________________________________\n");
    printf("                                                                   Next Tutorial -> D\n");
    printf("                                    Enter to Exit\n");
}

void seconfPageTutorial() {
    // multiplayer tutorial:
    printf("_____________________________________________________________________________________\n");
    printf(" Gunakan W, A, S, D untuk menggeraakan ular pertama.                  \n");
    printf(" Gunakan I, J, K, L untuk menggeraakan ular kedua.                     \n");
    printf(" Makan makanan sebanyak mungkin (*) untuk menambahkan panjang ular.    \n");
    printf(" Hindari menabrak dinding, tubuh uluar sendiri, maupun tubuh ular lawan                      \n");
    printf(" Ular yang menabrak akan kalah.                                        \n");
    printf("                       ########################################\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #         W               I            #\n");
    printf("                       #         ^               ^            #\n");
    printf("                       #         |               |            #\n");
    printf("                       #   W <-  "
           "\033[0;32m"
           "O"
           "\033[0m"
           "  -> D   I <-  "
           "\033[0;33m"
           "O"
           "\033[0m"
           "  -> L      #\n");
    printf("                       #         |               |            #\n");
    printf("                       #         v               v            #\n");
    printf("                       #         S               K            #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       #                                      #\n");
    printf("                       ########################################\n");
    printf("_____________________________________________________________________________________\n");
    printf(" A <- Previous Tutorial\n");
    printf("                                    Enter to Exit\n");
}

void showTutorial() {
    int showMode = 1;
    char input = 'a';

    // showMode 1 = tutorial for singlea player
    // showMode 2 = tutorial for multiplayer

    printf("                            SLITHER.io TUTORIAL                      \n");
    if (showMode == 1) {
        printf("            "
               "\033[0;32m"
               "Single Player"
               "\033[0m"
               "                         Multiplayer        \n");
    } else {
        printf("            Single Player                         "
               "\033[0;32m"
               "Multiplayer"
               "\033[0m"
               "        \n");
    }

    firstPageTutorial();

    while (1) {
        input = getch();
        if (input == 'd') {
            showMode = 2;
        } else if (input == 'a') {
            showMode = 1;
        } else if (input == 13) {
            break;
        }

        system("cls");
        printf("                            SLITHER.io TUTORIAL                      \n");
        if (showMode == 1) {
            printf("            "
                   "\033[0;32m"
                   "Single Player"
                   "\033[0m"
                   "                         Multiplayer        \n");
        } else {
            printf("            Single Player                         "
                   "\033[0;32m"
                   "Multiplayer"
                   "\033[0m"
                   "        \n");
        }

        if (showMode == 1) {
            firstPageTutorial();
        } else if (showMode == 2) {
            seconfPageTutorial();
        }
    }
}