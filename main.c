/*
SNAKE GAME

Christian Hadiwijaya
2306161952
*/

#include <conio.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define rows 20
#define cols 20

char world[cols][rows];
char lastKey;

typedef struct SnakeBody {
    int x;
    int y;
    struct SnakeBody *next;
} SnakeBody;

struct Snake {
    int length;
    SnakeBody *head;
    SnakeBody *tail;
};

int snakeX = 5;
int snakeY = 5;
bool isGameOver = false;

struct Snake Snake;

void printWorld() {
    int i;
    for (i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%c", world[i][j]);
        }
        printf("\n");
    }
}

void fillWorld() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == rows - 1) {
                world[i][j] = '#';
            } else if (!(world[i][j] == '*')) {
                world[i][j] = ' ';
            }
        }
    }
}

void fillSnake() {
    SnakeBody *current = Snake.head;
    while (current != NULL) {
        world[current->y][current->x] = 'o';
        current = current->next;
    }
}

void moveSnake(int x, int y) {
    int tempX = Snake.head->x;
    int tempY = Snake.head->y;

    Snake.head->x += x;
    Snake.head->y += y;

    SnakeBody *current = Snake.head->next;
    while (current != NULL) {
        int temp = current->x;
        current->x = tempX;
        tempX = temp;

        temp = current->y;
        current->y = tempY;
        tempY = temp;

        current = current->next;
    }
    // for (int i = 1; i <= Snake.length; i++) {
    //     Snake.body[Snake.length - i + 1].x = Snake.body[Snake.length - i].x;
    //     Snake.body[Snake.length - i + 1].y = Snake.body[Snake.length - i].y;
    // }

    // Snake.body[0].x += x;
    // Snake.body[0].y += y;
}

void readKey() {
    char key;

    if (kbhit()) {
        key = getch();
    } else {
        key = lastKey;
    }

    lastKey = key;

    switch (lastKey) {
    case 'w':
        moveSnake(0, -1);
        break;
    case 's':
        moveSnake(0, 1);
        break;
    case 'a':
        moveSnake(-1, 0);
        break;
    case 'd':
        moveSnake(1, 0);
        break;
    default:
        break;
    }
}

void addBody() {
    SnakeBody *newBody = (SnakeBody *)malloc(sizeof(SnakeBody));
    newBody->x = Snake.tail->x; // Place new segment at the tail's position
    newBody->y = Snake.tail->y;
    newBody->next = NULL; // New body is the new tail, so next is NULL

    Snake.tail->next = newBody; // Link the current tail to the new body
    Snake.tail = newBody;       // Update the tail to the new body
    Snake.length++;
}

void generateFood() {
    int x, y;

    x = rand() % (rows - 2) + 1;
    y = rand() % (cols - 2) + 1;

    if (world[y][x] == ' ') {
        {
            world[y][x] = '*';
        }
    } else {
        generateFood();
    }
}

void gameRules() {
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                if (Snake.head->x == 0 || Snake.head->x == rows - 1 || Snake.head->y == 0 || Snake.head->y == cols - 1) {
                    printf("Game Over\n");
                    isGameOver = true;
                }
            }

#pragma omp critical
            {
                SnakeBody *current = Snake.head->next;
                while (current != NULL) {
                    if (Snake.head->x == current->x && Snake.head->y == current->y) {
                        printf("Game Over\n");
                        isGameOver = true;
                    }
                    current = current->next;
                }
            }

#pragma omp task
            {
                if (world[Snake.head->y][Snake.head->x] == '*') {
                    addBody();
                    generateFood();
                }
            }
#pragma omp taskwait
        }
    }
}

int main() {
    Snake.length = 0;
    Snake.head = (SnakeBody *)malloc(sizeof(SnakeBody) * 100);
    Snake.head->x = snakeX;
    Snake.head->y = snakeY;
    Snake.head->next = NULL;
    Snake.tail = Snake.head;

    lastKey = 'd';

    srand(time(NULL));

    addBody();
    fillWorld();
    generateFood();

    while (!isGameOver) {
        system("cls");
        fillWorld();
        fillSnake();
        printWorld();
        readKey();
        gameRules();
        Sleep(250);
    }
}
