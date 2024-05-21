void print_title();
void print_gameOver();
void print_wait_3s();

int menu() {
    char code;
    int input = 0;

    do {
        print_title();

        int i;
        char select[4][3];
        for (i = 0; i < 4; i++) {
            strcpy(select[i], "");
        }
        char option[4][20];
        strcpy(option[0], "Singleplayer");
        strcpy(option[1], "Multiplayer");
        strcpy(option[2], "Leaderboard");
        strcpy(option[3], "Exit Game");

        strcpy(select[input], "-->");
        for (i = 0; i < 4; i++) {
            if (strcasecmp(select[i], "-->") == 0) {
                printf(GREEN "  %s %s\n" RESET, select[i], option[i]);
            } else {
                printf("  %s %s\n", select[i], option[i]);
            }
        }
        code = tolower(getch());

        switch (code) {
        case 'w':
            input--;
            if (input == -1) {
                input = 3;
            }
            break;
        case 's':
            input++;
            if (input == 4) {
                input = 0;
            }
            break;
        }
        system("cls");
    } while (code != '\r');

    return input + 1;
}

void print_title() {
    printf("                                                                                                          \n");
    printf("               ,--,                   ,----,                                                              \n");
    printf("            ,---.'|                 ,/   .`|       ,--,                                      ,----..      \n");
    printf("  .--.--.   |   | :      ,---,    ,`   .'  :     ,--.'|    ,---,.,-.----.           ,---,   /   /   \'    \n");
    printf(" /  /    '. :   : |   ,`--.' |  ;    ;     /  ,--,  | :  ,'  .' |\'    / \'       ,`--.' |  /   .     :   \n");
    printf("|  :  /`. / |   ' :   |   :  :.'___,/    ,',---.'|  : ',---.'   |;   :    \'      |   :  : .   /   ;.  \' \n");
    printf(";  |  |--`  ;   ; '   :   |  '|    :     | |   | : _' ||   |   .'|   | .\' :      :   |  '.   ;   /  ` ;  \n");
    printf("|  :  ;_    '   | |__ |   :  |;    |.';  ; :   : |.'  |:   :  |-,.   : |:  |      |   :  |;   |  ; \' ;|  \n");
    printf("\' \'    `. |   | :.'|'   '  ;`----'  |  | |   ' '  ; ::   |  ;/||   |  \' :      '   '  ;|   :  | ; | '  \n");
    printf("  `----.   \'   :    ;|   |  |    '   :  ; '   |  .'. ||   :   .'|   : .  /       |   |  |.   |  ' ' ' :  \n");
    printf("  __\' \'  ||   |  ./ '   :  ;    |   |  ' |   | :  | '|   |  |-,;   | |  \'      '   :  ;'   ;  \'; / |  \n");
    printf(" /  /`--'  /;   : ;   |   |  '    '   :  | '   : |  : ;'   :  ;/||   | ;\' \'     |   |  ' \'  \' ',  /   \n");
    printf("'--'.     / |   ,/    '   :  |    ;   |.'  |   | '  ,/ |   |    |'   ' | \'.'___  '   :  |  ;   :    /    \n");
    printf("  `--'---'  '---'     ;   |.'     '---'    ;   : ;--'  |   :   .':   : :-' /  . \';   |.'    \'  \'.'     \n");
    printf("                      '---'                |   ,/      |   | ,'  |   |.'   \' ; / '---'       `---`       \n");
    printf("                                           '---'       `----'    `---'      `--`                          \n");
    printf("                                                                                                          \n");
}

void print_gameOver() {
    printf("                                                                                                                \n");
    printf("                                      ____                         ,----..                                      \n");
    printf("  ,----..      ,---,                ,'  , `.     ,---,.           /   /   \'                 ,---,.,-.----.     \n");
    printf(" /   /   \'   '  .' \'           ,-+-,.' _ |   ,'  .' |          /   .     :        ,---.  ,'  .' |\'   /  \'   \n");
    printf("|   :     :  /  ;    '.       ,-+-. ;   , || ,---.'   |         .   /   ;.  \'     /__./|,---.'   |;   :    \'  \n");
    printf(".   |  ;. / :  :       \'    ,--.'|'   |  ;| |   |   .'        .   ;   /  ` ; ,---.;  ; ||   |   .'|   | .\':   \n");
    printf(".   ; /--`  :  |   /\'  \'  |   |  ,', |  ': :   :  |-,        ;   |  ; \\; |/___/ \' | |:   :  |-,.   : |: |   \n");
    printf(";   | ;  __ |  :  ' ;.   :  |   | /  | |  || :   |  ;/|        |   :  | ; | '\'  ;  \'' |:   |  ;/||   |  \':   \n");
    printf("|   : |.' .'|  |  ;/  \'  \'|'   | :  | :  | |   :   .'        .   |  ' ' ' : \'  \' \' ||   :   .'|   : .  /   \n");
    printf(".   | '_.' :'  :  | \' \',' ;   . |  ; |--'  |   |  |-,        '   ;  \\;/  |  ;   \' ' .|   |  |-,;   | |  \'  \n");
    printf("'   ; : |  ||  |  '  '--'   |   : |  | ,     '   :  ;/|         \\  \\ ',  /    \'  \'  ''   :  ;/||   | ;\' \' \n");
    printf("'   | '/  .'|  :  :         |   : '  |/      |   |    |         ;   :    /       \'  ` ; |   |    |'   ' | \' ' \n");
    printf("|   :    /  |  | ,'         ;   | |`-'       |   :   .'           \\  \\.'        :   \'||   :   .':   : :-'    \n");
    printf(" \'  \'.'   `--''           |   ;/           |   | ,'              `---`           '---` |   | ,'  |   |.'      \n");
    printf("  `---`                     '---'            `----'                                      `----'    `---'        \n");
    printf("                                                                                                                \n");
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