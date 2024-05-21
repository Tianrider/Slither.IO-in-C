#include <conio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define rows 20
#define cols 40

typedef struct SnakeBody {
    int x;
    int y;
    struct SnakeBody *next;
} SnakeBody;

typedef struct Snake {
    int length;
    SnakeBody *head;
    SnakeBody *tail;
} Snake;

void printWorld(int playerOneScore, int playerTwoScore, char world[cols][rows]) {
    int i;
    printf("Player 1 Score: %-10d Player 2 Score: %d\n", playerOneScore, playerTwoScore);
    for (i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (world[j][i] == 'o') {
                printf("\033[0;32mo\033[0m");
            } else if (world[j][i] == 'x') {
                // yellow
                printf("\033[0;33mx\033[0m");
            } else if (world[j][i] == '*') {
                // red
                printf("\033[0;31m*\033[0m");
            } else {
                printf("%c", world[j][i]);
            }
        }
        printf("\n");
    }
}

void multi_printWorldOver(int playerOneScore, int playerTwoScore, int losingPlayer, char world[cols][rows]) {
    printf("Player 1 Score: %-10d Player 2 Score: %d\n", playerOneScore, playerTwoScore);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (world[j][i] == 'o') {
                if (losingPlayer == 2) {
                    printf("\033[0;31mo\033[0m");
                } else {
                    printf("\033[0;32mo\033[0m");
                }
            } else if (world[j][i] == 'x') {
                if (losingPlayer == 1) {
                    printf("\033[0;31mx\033[0m");
                } else {
                    printf("\033[0;33mx\033[0m");
                }
            } else if (world[j][i] == '*') {
                printf("\033[0;31m*\033[0m");
            } else {
                printf("%c", world[j][i]);
            }
        }
        printf("\n");
    }
}

void fillWorld(char world[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                world[j][i] = '#';
            } else if (!(world[j][i] == '*')) {
                world[j][i] = ' ';
            }
        }
    }
}

void fillSnake(char world[cols][rows], Snake *snakeOne, Snake *snakeTwo) {
    SnakeBody *current = snakeOne->head;
    while (current != NULL) {
        world[current->x][current->y] = 'o';
        current = current->next;
    }
    current = snakeTwo->head;
    while (current != NULL) {
        world[current->x][current->y] = 'x';
        current = current->next;
    }
}

void moveSnake(int snake, int x, int y, Snake *snakeOne, Snake *snakeTwo) {
    struct Snake *currentSnake;
    if (snake == 0) {
        currentSnake = snakeOne;
    } else {
        currentSnake = snakeTwo;
    }

    int tempX = currentSnake->head->x;
    int tempY = currentSnake->head->y;

    currentSnake->head->x += x;
    currentSnake->head->y += y;

    SnakeBody *current = currentSnake->head->next;
    while (current != NULL) {
        int temp = current->x;
        current->x = tempX;
        tempX = temp;

        temp = current->y;
        current->y = tempY;
        tempY = temp;

        current = current->next;
    }
}

void addBody(Snake *snake) {
    SnakeBody *newBody = (SnakeBody *)malloc(sizeof(SnakeBody));
    newBody->x = snake->tail->x;
    newBody->y = snake->tail->y;
    newBody->next = NULL;
    snake->tail->next = newBody;
    snake->tail = newBody;
    snake->length++;
}

void readKeyOne(char *lastKeyOne, char *lastKeyTwo, Snake *snakeOne, Snake *snakeTwo) {
    char key;

    if (kbhit()) {
        key = getch();
    } else {
        key = *lastKeyOne;
    }

    if (key == 'i' || key == 'k' || key == 'j' || key == 'l') {
        *lastKeyTwo = key;
    } else {
        *lastKeyOne = key;
    }

    switch (*lastKeyOne) {
    case 'w':
        moveSnake(0, 0, -1, snakeOne, snakeTwo);
        break;
    case 's':
        moveSnake(0, 0, 1, snakeOne, snakeTwo);
        break;
    case 'a':
        moveSnake(0, -1, 0, snakeOne, snakeTwo);
        break;
    case 'd':
        moveSnake(0, 1, 0, snakeOne, snakeTwo);
        break;
    default:
        break;
    }

    switch (*lastKeyTwo) {
    case 'i':
        moveSnake(1, 0, -1, snakeOne, snakeTwo);
        break;
    case 'k':
        moveSnake(1, 0, 1, snakeOne, snakeTwo);
        break;
    case 'j':
        moveSnake(1, -1, 0, snakeOne, snakeTwo);
        break;
    case 'l':
        moveSnake(1, 1, 0, snakeOne, snakeTwo);
        break;
    default:
        break;
    }
}

void generateFood(char world[cols][rows]) {
    int x = rand() % (cols - 2) + 1;
    int y = rand() % (rows - 2) + 1;

    if (world[x][y] == ' ') {
        world[x][y] = '*';
    } else {
        generateFood(world);
    }
}

void checkCollision(bool *isGameOver, int *winner, int *playerOneScore, int *playerTwoScore, Snake *snakeOne, Snake *snakeTwo, char world[cols][rows]) {
    if (snakeOne->head->x == 0 || snakeOne->head->x == cols - 1 || snakeOne->head->y == 0 || snakeOne->head->y == rows - 1) {
        *isGameOver = true;
        *winner = 2;
    }

    if (snakeTwo->head->x == 0 || snakeTwo->head->x == cols - 1 || snakeTwo->head->y == 0 || snakeTwo->head->y == rows - 1) {
        *isGameOver = true;
        *winner = 1;
    }

    SnakeBody *current = snakeOne->head->next;
    while (current != NULL) {
        if (current->x == snakeOne->head->x && current->y == snakeOne->head->y) {
            *isGameOver = true;
            *winner = 2;
        }
        current = current->next;
    }

    current = snakeTwo->head->next;
    while (current != NULL) {
        if (current->x == snakeTwo->head->x && current->y == snakeTwo->head->y) {
            *isGameOver = true;
            *winner = 1;
        }
        current = current->next;
    }

    // check if player 1 eats player 2
    current = snakeTwo->head;
    while (current != NULL) {
        if (current->x == snakeOne->head->x && current->y == snakeOne->head->y) {
            *isGameOver = true;
            *winner = 2;
        }
        current = current->next;
    }

    // check if player 2 eats player 1
    current = snakeOne->head;
    while (current != NULL) {
        if (current->x == snakeTwo->head->x && current->y == snakeTwo->head->y) {
            *isGameOver = true;
            *winner = 1;
        }
        current = current->next;
    }

    // check if head meets head, find the highest score
    if (snakeOne->head->x == snakeTwo->head->x && snakeOne->head->y == snakeTwo->head->y) {
        if (*playerOneScore > *playerTwoScore) {
            *isGameOver = true;
            *winner = 1;
        } else {
            *isGameOver = true;
            *winner = 2;
        }
    }

    // check food
    if (world[snakeOne->head->x][snakeOne->head->y] == '*') {
        *playerOneScore += 4;
        addBody(snakeOne);
        generateFood(world);
    }

    if (world[snakeTwo->head->x][snakeTwo->head->y] == '*') {
        *playerTwoScore += 4;
        addBody(snakeTwo);
        generateFood(world);
    }
}

void printPlayerOneWin() {
    printf("\033[0;32m");
    printf("                                                                                                    \n");
    printf(" _|_|_|    _|                                                _|      _|          _|  _|             \n");
    printf(" _|    _|  _|    _|_|_|  _|    _|    _|_|    _|  _|_|      _|_|      _|          _|      _|_|_|     \n");
    printf(" _|_|_|    _|  _|    _|  _|    _|  _|_|_|_|  _|_|            _|      _|    _|    _|  _|  _|    _|   \n");
    printf(" _|        _|  _|    _|  _|    _|  _|        _|              _|        _|  _|  _|    _|  _|    _|   \n");
    printf(" _|        _|    _|_|_|    _|_|_|    _|_|_|  _|              _|          _|  _|      _|  _|    _|   \n");
    printf("                               _|                                                                   \n");
    printf("                           _|_|                                                                     \n");
    printf("\033[0m");

    while (getch() != '\r') {
    }
}

void printPlayerTwoWin() {
    printf("\033[0;32m");
    printf("                                                                                                        \n");
    printf(" _|_|_|    _|                                                _|_|        _|          _|  _|             \n");
    printf(" _|    _|  _|    _|_|_|  _|    _|    _|_|    _|  _|_|      _|    _|      _|          _|      _|_|_|     \n");
    printf(" _|_|_|    _|  _|    _|  _|    _|  _|_|_|_|  _|_|              _|        _|    _|    _|  _|  _|    _|   \n");
    printf(" _|        _|  _|    _|  _|    _|  _|        _|              _|            _|  _|  _|    _|  _|    _|   \n");
    printf(" _|        _|    _|_|_|    _|_|_|    _|_|_|  _|            _|_|_|_|          _|  _|      _|  _|    _|   \n");
    printf("                               _|                                                                       \n");
    printf("                           _|_|                                                                         \n");
    printf("\033[0m");

    while (getch() != '\r') {
    }
}

void multi_clearGame(Snake *snakeOne, Snake *snakeTwo, char world[cols][rows]) {
    SnakeBody *current = snakeOne->head;
    SnakeBody *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    current = snakeTwo->head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    snakeOne->length = 0;
    snakeOne->head = NULL;
    snakeOne->tail = NULL;

    snakeTwo->length = 0;
    snakeTwo->head = NULL;
    snakeTwo->tail = NULL;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            world[j][i] = ' ';
        }
    }
}

void multi_gameOverEffect(int playerOneScore, int playerTwoScore, int losingPlayer, char world[cols][rows]) {
    int winner;
    if (losingPlayer == 1) {
        winner = 2;
    } else {
        winner = 1;
    }
    for (int i = 0; i < 5; i++) {
        system("cls");
        multi_printWorldOver(playerOneScore, playerTwoScore, losingPlayer, world);
        Sleep(300);
        system("cls");
        printWorld(playerOneScore, playerTwoScore, world);
        Sleep(300);
    }
}

void startTwoPlayer() {
    char world[cols][rows];
    Snake snakeOne;
    Snake snakeTwo;
    bool isGameOver = false;
    int winner = 0;
    int playerOneScore = 0;
    int playerTwoScore = 0;
    char lastKeyOne = 'w';
    char lastKeyTwo = 'i';

    fillWorld(world);
    isGameOver = false;
    playerOneScore = 0;
    playerTwoScore = 0;

    srand(time(NULL));
    snakeOne.length = 1;
    snakeOne.head = (SnakeBody *)malloc(sizeof(SnakeBody));
    snakeOne.head->x = 10;
    snakeOne.head->y = 10;
    snakeOne.head->next = NULL;
    snakeOne.tail = snakeOne.head;

    snakeTwo.length = 1;
    snakeTwo.head = (SnakeBody *)malloc(sizeof(SnakeBody));
    snakeTwo.head->x = 30;
    snakeTwo.head->y = 10;
    snakeTwo.head->next = NULL;
    snakeTwo.tail = snakeTwo.head;

    world[10][10] = 'o';
    world[30][10] = 'x';

    fillWorld(world);
    generateFood(world);
    generateFood(world);

    while (!isGameOver) {
        fillWorld(world);
        fillSnake(world, &snakeOne, &snakeTwo);
        printWorld(playerOneScore, playerTwoScore, world);
        readKeyOne(&lastKeyOne, &lastKeyTwo, &snakeOne, &snakeTwo);
        checkCollision(&isGameOver, &winner, &playerOneScore, &playerTwoScore, &snakeOne, &snakeTwo, world);
        Sleep(300);
        system("cls");
    }

    multi_gameOverEffect(playerOneScore, playerTwoScore, winner, world);

    system("cls");
    if (winner == 1) {
        printPlayerOneWin();
    } else {
        printPlayerTwoWin();
    }

    multi_clearGame(&snakeOne, &snakeTwo, world);
}
