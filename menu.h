#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void print_title();
void print_gameOver();
void printLeaderboard();
void print_wait_3s();
void print_Thankyou();

int menu() {
    char code;
    int input = 0;

    do {
        print_title();

        int i;
        char select[5][3];
        for (i = 0; i < 5; i++) {
            strcpy(select[i], "");
        }
        char option[5][20];
        strcpy(option[0], "Singleplayer");
        strcpy(option[1], "Multiplayer");
        strcpy(option[2], "Leaderboard");
        strcpy(option[3], "Tutorial");
        strcpy(option[4], "Exit Game");

        strcpy(select[input], "-->");
        for (i = 0; i < 5; i++) {
            if (strcasecmp(select[i], "-->") == 0) {
                printf("\033[0;32m"
                       "  %+80s %s\n"
                       "\033[0;0m",
                       select[i], option[i]);
            } else {
                printf("  %+80s %s\n", select[i], option[i]);
            }
        }

        code = tolower(getch());

        switch (code) {
        case 'w':
            // Jika input = -1, maka input = 4
            input--;
            if (input == -1) {
                input = 4;
            }
            break;
        case 's':
            // Jika input = 5, maka input = 0
            input++;
            if (input == 5) {
                input = 0;
            }
            break;
        }
        system("cls");
    } while (code != '\r');

    return input + 1;
}

int confirmSameUser(char nama[]) {
    char code;
    int input = 0;
    do {
        system("cls");
        printf("\n\n\n\n\n\n Username %s Sudah Ada! Apakah Anda ingin bermain dengan username ini? (hanya nilai tertinggi yang akan disimpan)\n", nama);

        char select[2][3];
        for (int i = 0; i < 2; i++) {
            strcpy(select[i], "");
        }

        char option[2][20];
        strcpy(option[0], "Ya");
        strcpy(option[1], "Tidak");

        strcpy(select[input], "-->");
        for (int i = 0; i < 2; i++) {
            if (strcasecmp(select[i], "-->") == 0) {
                printf("\033[0;32m"
                       "  %s %s\n"
                       "\033[0;0m",
                       select[i], option[i]);
            } else {
                printf("  %s %s\n", select[i], option[i]);
            }
        }

        code = tolower(getch());

        switch (code) {
        case 'w':
            input--;
            if (input == -1) {
                input = 1;
            }
            break;
        case 's':
            input++;
            if (input == 2) {
                input = 0;
            }
            break;
        }
        system("cls");
    } while (code != '\r');

    return input;
}

void print_title() {
    printf("\033[0;34m");
    printf("                                                                                                                                          \n");
    printf("--..,_                     _,.--.               _|_|_|  _|        _|_|_|  _|_|_|_|_|  _|    _|  _|_|_|_|  _|_|_|        _|_|_|    _|_|    \n");
    printf("   `'.'.                .'`__ o  `;__.        _|        _|          _|        _|      _|    _|  _|        _|    _|        _|    _|    _|  \n");
    printf("      '.'.            .'.'`  '---'`  `          _|_|    _|          _|        _|      _|_|_|_|  _|_|_|    _|_|_|          _|    _|    _|  \n");
    printf("        '.`'--....--'`.'                            _|  _|          _|        _|      _|    _|  _|        _|    _|        _|    _|    _|  \n");
    printf("          `'--....--'`                        _|_|_|    _|_|_|_|  _|_|_|      _|      _|    _|  _|_|_|_|  _|    _|  _|  _|_|_|    _|_|    \n");
    printf("                                                                                                                                          \n");
    printf("                                                                                                                                          \n");
    printf("\033[0m");
}

void print_gameOver(char nama[], int score) {
    printf("\033[0;31m");
    printf("                                                                                         \n");
    printf("   _|_|_|    _|_|    _|      _|  _|_|_|_|        _|_|    _|      _|  _|_|_|_|  _|_|_|    \n");
    printf(" _|        _|    _|  _|_|  _|_|  _|            _|    _|  _|      _|  _|        _|    _|  \n");
    printf(" _|  _|_|  _|_|_|_|  _|  _|  _|  _|_|_|        _|    _|  _|      _|  _|_|_|    _|_|_|    \n");
    printf(" _|    _|  _|    _|  _|      _|  _|            _|    _|    _|  _|    _|        _|    _|  \n");
    printf("   _|_|_|  _|    _|  _|      _|  _|_|_|_|        _|_|        _|      _|_|_|_|  _|    _|  \n");
    printf("                                                                                         \n");
    printf("                                                                                         \n");
    printf("\033[0m");

    printf("%s\n", nama);
    printf("Score: %d\n", score);

    while (getch() != '\r') {
    }
}

void printLeaderboard() {
    printf("\033[0;36m");
    printf("                                                                                                               \n");
    printf(" _|        _|_|_|_|    _|_|    _|_|_|    _|_|_|_|  _|_|_|    _|_|_|      _|_|      _|_|    _|_|_|    _|_|_|    \n");
    printf(" _|        _|        _|    _|  _|    _|  _|        _|    _|  _|    _|  _|    _|  _|    _|  _|    _|  _|    _|  \n");
    printf(" _|        _|_|_|    _|_|_|_|  _|    _|  _|_|_|    _|_|_|    _|_|_|    _|    _|  _|_|_|_|  _|_|_|    _|    _|  \n");
    printf(" _|        _|        _|    _|  _|    _|  _|        _|    _|  _|    _|  _|    _|  _|    _|  _|    _|  _|    _|  \n");
    printf(" _|_|_|_|  _|_|_|_|  _|    _|  _|_|_|    _|_|_|_|  _|    _|  _|_|_|      _|_|    _|    _|  _|    _|  _|_|_|    \n");
    printf("                                                                                                               \n");
    printf("                                                                                                               \n");
    printf("\033[0m");
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

void print_wait_3s() {
    system("cls");
    printf("                 \n");
    printf("  .--,--``-.     \n");
    printf(" /    /     '.   \n");
    printf("/ .. /        ;  \n");
    printf("\'`` \' .`-    ' \n");
    printf(" \'___\'/  \'  : \n");
    printf("      \'  :   |  \n");
    printf("      /  /   /   \n");
    printf("      \' \'  \'  \n");
    printf("  ___ /   :   |  \n");
    printf(" /   /\'  /   :  \n");
    printf("/ ,,/  ',-    .  \n");
    printf("\'''\'       ;   \n");
    printf(" \'  \'    .'    \n");
    printf("  `--`-,,-'      \n");
    printf("                 \n");

    Sleep(1000);
    system("cls");
    printf("               \n");
    printf("               \n");
    printf("      ,----,   \n");
    printf("    .'   .' \' \n");
    printf("  ,----,'    | \n");
    printf("  |    :  .  ; \n");
    printf("  ;    |.'  /  \n");
    printf("  `----'/  ;   \n");
    printf("    /  ;  /    \n");
    printf("   ;  /  /-,   \n");
    printf("  /  /  /.`|   \n");
    printf("./__;      :   \n");
    printf("|   :    .'    \n");
    printf(";   | .'       \n");
    printf("`---'          \n");
    printf("               \n");

    Sleep(1000);
    system("cls");
    printf("           \n");
    printf("           \n");
    printf("     ,---, \n");
    printf("  ,`--.' | \n");
    printf(" /    /  : \n");
    printf(":    |.' ' \n");
    printf("`----':  | \n");
    printf("   '   ' ; \n");
    printf("   |   | | \n");
    printf("   '   : ; \n");
    printf("   |   | ' \n");
    printf("   '   : | \n");
    printf("   ;   |.' \n");
    printf("   '---'   \n");
    printf("           \n");
    printf("           \n");

    Sleep(1000);
    system("cls");
}

void print_Thankyou() {
    printf("\033[0;35m");
    printf("                                                                                       \n");
    Sleep(300);
    printf(" _|_|_|_|_|  _|    _|    _|_|    _|      _|  _|    _|  _|      _|    _|_|    _|    _|  \n");
    Sleep(300);
    printf("     _|      _|    _|  _|    _|  _|_|    _|  _|  _|      _|  _|    _|    _|  _|    _|  \n");
    Sleep(300);
    printf("     _|      _|_|_|_|  _|_|_|_|  _|  _|  _|  _|_|          _|      _|    _|  _|    _|  \n");
    Sleep(300);
    printf("     _|      _|    _|  _|    _|  _|    _|_|  _|  _|        _|      _|    _|  _|    _|  \n");
    Sleep(300);
    printf("     _|      _|    _|  _|    _|  _|      _|  _|    _|      _|        _|_|      _|_|    \n");
    printf("                                                                                       \n");
    printf("\033[0m");
}
