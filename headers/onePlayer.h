#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define single_rows 20
#define single_cols 20

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

typedef struct single_SnakeBody { // linked list untuk snake body
    int x;                        // setiap snake body akan memiliki koordinat nya sendiri
    int y;
    struct single_SnakeBody *next;
} single_SnakeBody;

typedef struct single_Snake { // struct snake untuk memudahkan mengetahui posisi kepala dan ekor ular
    int length;               // simpan panjang ular
    single_SnakeBody *head;
    single_SnakeBody *tail;
} single_Snake;

// menampilkan world ke layar
void single_printWorld(char single_world[single_cols][single_rows], int single_score) {
    int i;
    printf("Score: %d\n", single_score);
    for (i = 0; i < single_rows; i++) {
        for (int j = 0; j < single_cols; j++) {
            if (single_world[i][j] == 'o') {
                printf("%s%c%s", GREEN, single_world[i][j], RESET);
            } else if (single_world[i][j] == '*') {
                printf("%s%c%s", RED, single_world[i][j], RESET);
            } else {
                printf("%c", single_world[i][j]);
            }
        }
        printf("\n");
    }
}

// menampilkan world ke layar ketika game over
void single_printWorldOver(char single_world[single_cols][single_rows], int single_score) {
    printf("Score: %d\n", single_score);
    for (int i = 0; i < single_rows; i++) {
        for (int j = 0; j < single_cols; j++) {
            if (single_world[i][j] == 'o') {
                printf("%s%c%s", RED, single_world[i][j], RESET);
            } else if (single_world[i][j] == '*') {
                printf("%s%c%s", RED, single_world[i][j], RESET);
            } else {
                printf("%c", single_world[i][j]);
            }
        }
        printf("\n");
    }
}

// mengisi world dengan '#' di pinggir dan ' ' di dalam
void single_fillWorld(char single_world[single_cols][single_rows]) {
#pragma omp parallel for
    for (int i = 0; i < single_rows; i++) {
        for (int j = 0; j < single_cols; j++) {
            if (i == 0 || i == single_rows - 1 || j == 0 || j == single_cols - 1) {
                single_world[i][j] = '#';
            } else if (single_world[i][j] != '*') {
                single_world[i][j] = ' ';
            }
        }
    }
}

// mengisi snake ke dalam world sesuai koordinatnya
void single_fillSnake(char single_world[single_cols][single_rows], single_Snake *snake) {
    single_SnakeBody *current = snake->head;
#pragma omp parallel
    {
#pragma omp single
        {
            while (current != NULL) {
#pragma omp task firstprivate(current)
                {
                    single_world[current->y][current->x] = 'o';
                }
                current = current->next;
            }
        }
    }
}

// menggerakan snake sesuai direction tiap frame
void single_moveSnake(single_Snake *snake, int x, int y) {
    int tempX = snake->head->x;
    int tempY = snake->head->y;

    snake->head->x += x;
    snake->head->y += y;

    single_SnakeBody *current = snake->head->next;
#pragma omp parallel
    {
#pragma omp single
        {
            while (current != NULL) {
#pragma omp task firstprivate(current)
                {
#pragma omp critical
                    {
                        int temp = current->x;
                        current->x = tempX;
                        tempX = temp;

                        temp = current->y;
                        current->y = tempY;
                        tempY = temp;
                    }
                }
                current = current->next;
#pragma omp taskwait
            }
        }
    }
}

void single_readKey(char *lastKey) {
    if (_kbhit()) {
        *lastKey = _getch();
    }
}

// menambahkan snake body di belakang ular
void single_addBody(single_Snake *snake) {
    single_SnakeBody *newBody = (single_SnakeBody *)malloc(sizeof(single_SnakeBody));
    if (newBody == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newBody->x = snake->tail->x;
    newBody->y = snake->tail->y;
    newBody->next = NULL;

    snake->tail->next = newBody;
    snake->tail = newBody;
    snake->length++;
}

// mengenerate makanan di world secara random
void single_generateFood(char single_world[single_cols][single_rows]) {
    int x, y;

    do {
        x = rand() % (single_rows - 2) + 1;
        y = rand() % (single_cols - 2) + 1;
    } while (single_world[y][x] != ' ');

    single_world[y][x] = '*';
}

void gameOverEffect(char single_world[single_cols][single_rows], int single_score) {
    for (int i = 0; i < 5; i++) {
        system("cls");
        single_printWorldOver(single_world, single_score);
        Sleep(250);
        system("cls");
        single_printWorld(single_world, single_score);
        Sleep(250);
    }

    system("cls");
}

// rules game yang akan di cek setiap frame
void single_gameRules(char single_world[single_cols][single_rows], single_Snake *snake, int *score, bool *isGameOver) {
    single_SnakeBody *current = snake->head->next;

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                // cek jika snake mengenai border
                if (snake->head->x == 0 || snake->head->x == single_rows - 1 || snake->head->y == 0 || snake->head->y == single_cols - 1) {
                    gameOverEffect(single_world, *score);
                    *isGameOver = true;
                }
            }

#pragma omp task
            {
                // cek jika snake makan makanan
                if (single_world[snake->head->y][snake->head->x] == '*') {
                    single_addBody(snake);
                    single_generateFood(single_world);
                    *score += 4;
                }
            }

            while (current != NULL) {
#pragma omp task
                {
                    // cek jika snake menabrak badannya sendiri
                    if (snake->head->x == current->x && snake->head->y == current->y) {
                        gameOverEffect(single_world, *score);
                        *isGameOver = true;
                    }
                }
                current = current->next;
            }

#pragma omp taskwait
        }
    }
}

//  membersihkan game
void clearGame(single_Snake *snake, char single_world[single_cols][single_rows]) {
    single_SnakeBody *current = snake->head;
    single_SnakeBody *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    snake->length = 0;
    snake->head = NULL;
    snake->tail = NULL;

    for (int i = 0; i < single_rows; i++) {
        for (int j = 0; j < single_cols; j++) {
            single_world[i][j] = ' ';
        }
    }
}

// inisialisasi game single player
int single_startSinglePlayer() {
    char single_world[single_cols][single_rows];
    int single_score = 0;
    bool single_isGameOver = false;
    single_Snake single_Snake;
    int single_snakeX = 5;
    int single_snakeY = 5;
    char single_lastKey = 'd';

    single_fillWorld(single_world);
    single_score = 0;
    single_isGameOver = false;
    single_Snake.length = 1; // Initialize length to 1
    single_Snake.head = (single_SnakeBody *)malloc(sizeof(single_SnakeBody));
    if (single_Snake.head == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    single_Snake.head->x = single_snakeX;
    single_Snake.head->y = single_snakeY;
    single_Snake.head->next = NULL;
    single_Snake.tail = single_Snake.head;

    srand(time(NULL));

    single_addBody(&single_Snake);
    single_fillWorld(single_world);
    single_generateFood(single_world);

    // looping frame game
    while (!single_isGameOver) {
        system("cls");
        single_fillWorld(single_world);
        single_fillSnake(single_world, &single_Snake);
        single_printWorld(single_world, single_score);
        single_readKey(&single_lastKey);

        int dx = 0, dy = 0;
        if (single_lastKey == 'w') {
            dx = 0;
            dy = -1;
        } else if (single_lastKey == 's') {
            dx = 0;
            dy = 1;
        } else if (single_lastKey == 'a') {
            dx = -1;
            dy = 0;
        } else if (single_lastKey == 'd') {
            dx = 1;
            dy = 0;
        }

        single_moveSnake(&single_Snake, dx, dy);
        single_gameRules(single_world, &single_Snake, &single_score, &single_isGameOver);
        Sleep(300);
    }

    clearGame(&single_Snake, single_world);

    return single_score;
}