/*
    SLITHER.IO IN C

    Proyek Akhir Pemograman Lanjut - Kelompok 8

    Benedict Aurelius -2306209095
    Christian Hadiwijaya - 2306161952

    Ini adalah game Slither.io yang dibuat menggunakan bahasa C. Game ini dimainkan di terminal dengan cara melakukan refreshing layar setiap detiknya.
    Game ini memiliki beberapa fitur, yaitu:
    - Simpan high score pemain di file
    - Multiplayer (2 pemain)
    - Leaderboard untuk pemain dengan score tertinggi

    Version 1.0
*/

#include "leaderboard.h"
#include "menu.h"
#include "onePlayer.h"
#include "tutorial.h"
#include "twoPlayer.h"
#include <conio.h>
#include <ctype.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
    int option;
    int score;
    char nama[100];

    do {
        system("cls");
        option = menu();
        switch (option) {
        case 1: // singleplayer
            printf("\n\n\n\n\n\n\n %+70s", GREEN "Username: " RESET);
            scanf(" %[^\n]s", nama);
            print_wait_3s();
            score = single_startSinglePlayer();
            print_gameOver();
            leaderboard(nama, &score);
            break;
        case 2: // two player
            print_wait_3s();
            startTwoPlayer();
            break;
        case 3: // show leaderboard
            printLeaderboard();
            showLeaderboard();
            break;
        case 4:
            showTutorial();
            break;
        case 5: // exit game
            print_Thankyou();
            Sleep(1000);
            break;
        }
    } while (option != 5);

    return 0;
}