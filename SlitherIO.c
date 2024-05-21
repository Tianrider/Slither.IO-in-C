<<<<<<< HEAD
/*
    SLITHER.IO IN C
    Created by:
    Benedict Aurelius - 2306209095
    Christian Hadiwijaya - 2306161952

    PROYEK AKHIR PROGLAN

    Version 1.0
*/

#include <conio.h>
=======
#include "onePlayer.h"
#include "twoPlayer.h"
#include <conio.h>
#include <ctype.h>
>>>>>>> tian
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
<<<<<<< HEAD
#include <ctype.h>
#include "onePlayer.h"
#include "twoPlayer.h"
#include "leaderboard.h"
=======
// #include "leaderboard.h"
>>>>>>> tian
#include "menu.h"

int main() {
    int option;
    int score;
    char nama[50];

    do {
<<<<<<< HEAD
        option = menu();
        system("cls");
        switch(option) {
            case 1:
                // Single Player
                printf("Username: ");
                scanf("%s", nama);
                print_wait_3s();
                score = 0;
                multi_startSinglePlayer(&score);
                leaderboard(nama, &score);
                break;
            case 2:
                // Local Multiplayer
                startTwoPlayer();
                break;
            case 3:
                // Display Leaderboard
                showLeaderboard();
                break;
            case 4:
                // Exit
                print_Thankyou();
                Sleep(1000);
                break;
        }
    } while(option != 4);
=======
        system("cls");
        option = menu();
        switch (option) {
        case 1:
            printf("Username: ");
            scanf("%s", nama);
            print_wait_3s();
            multi_startSinglePlayer();
            // leaderboard(nama, &score);
            break;
        case 2:
            // multiPlayer();
            startTwoPlayer();
            break;
        case 3:
            // showLeaderboard();
            break;
        case 4:
            printf("Thank you for playing!\n");
            getch();
            break;
        }
    } while (option != 4);
>>>>>>> tian

    return 0;
}