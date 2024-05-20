#include "onePlayer.h"
#include "twoPlayer.h"
#include <conio.h>
#include <ctype.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
// #include "leaderboard.h"
#include "menu.h"

int main() {
    int option;
    int score;
    char nama[50];

    do {
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

    return 0;
}