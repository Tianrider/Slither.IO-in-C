#define multi_rows 20
#define multi_cols 20

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

char multi_world[multi_cols][multi_rows];
char multi_lastKey;

typedef struct multi_SnakeBody {
    int x;
    int y;
    struct multi_SnakeBody *next;
} multi_SnakeBody;

struct multi_Snake {
    int length;
    multi_SnakeBody *head;
    multi_SnakeBody *tail;
};

int multi_snakeX = 5;
int multi_snakeY = 5;
bool multi_isGameOver = false;

struct multi_Snake multi_Snake;

void multi_printWorld(int *score) {
    int i;
    printf("Score: %d\n", *score);
    for (i = 0; i < multi_rows; i++) {
        for (int j = 0; j < multi_rows; j++) {
            if (multi_world[i][j] == 'o') {
                printf("%s%c%s", GREEN, multi_world[i][j], RESET);
            } else if (multi_world[i][j] == '*') {
                printf("%s%c%s", RED, multi_world[i][j], RESET);
            } else {
                printf("%c", multi_world[i][j]);
            }
        }
        printf("\n");
    }
}

void multi_fillWorld() {
    for (int i = 0; i < multi_rows; i++) {
        for (int j = 0; j < multi_rows; j++) {
            if (i == 0 || i == multi_rows - 1 || j == 0 || j == multi_rows - 1) {
                multi_world[i][j] = '#';
            } else if (!(multi_world[i][j] == '*')) {
                multi_world[i][j] = ' ';
            }
        }
    }
}

void multi_fillSnake() {
    multi_SnakeBody *current = multi_Snake.head;
    while (current != NULL) {
        multi_world[current->y][current->x] = 'o';
        current = current->next;
    }
}

void multi_moveSnake(int x, int y) {
    int tempX = multi_Snake.head->x;
    int tempY = multi_Snake.head->y;

    multi_Snake.head->x += x;
    multi_Snake.head->y += y;

    multi_SnakeBody *current = multi_Snake.head->next;
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

void multi_readKey() {
    char key;

    if (kbhit()) {
        key = getch();
    } else {
        key = multi_lastKey;
    }

    multi_lastKey = key;

    switch (multi_lastKey) {
    case 'w':
        multi_moveSnake(0, -1);
        break;
    case 's':
        multi_moveSnake(0, 1);
        break;
    case 'a':
        multi_moveSnake(-1, 0);
        break;
    case 'd':
        multi_moveSnake(1, 0);
        break;
    default:
        break;
    }
}

void multi_addBody() {
    multi_SnakeBody *newBody = (multi_SnakeBody *)malloc(sizeof(multi_SnakeBody));
    newBody->x = multi_Snake.tail->x;
    newBody->y = multi_Snake.tail->y;
    newBody->next = NULL;

    multi_Snake.tail->next = newBody;
    multi_Snake.tail = newBody;
    multi_Snake.length++;
}

void multi_generateFood() {
    int x, y;

    for (int i = 0; i < multi_rows; i++) {
        for (int j = 0; j < multi_cols; j++) {
            if (multi_world[i][j] == '*') {
                multi_world[i][j] = ' ';
            }
        }
    }

    x = rand() % (multi_rows - 2) + 1;
    y = rand() % (multi_cols - 2) + 1;

    if (multi_world[y][x] == ' ') {
        multi_world[y][x] = '*';
    } else {
        multi_generateFood();
    }
}


void multi_gameRules(int *score) {
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            {
                if (multi_Snake.head->x == 0 || multi_Snake.head->x == multi_rows - 1 || multi_Snake.head->y == 0 || multi_Snake.head->y == multi_cols - 1) {
                    system("cls");
                    print_gameOver();
                    multi_isGameOver = true;
                }
            }

#pragma omp critical
            {
                multi_SnakeBody *current = multi_Snake.head->next;
                while (current != NULL) {
                    if (multi_Snake.head->x == current->x && multi_Snake.head->y == current->y) {
                        system("cls");
                        print_gameOver();
                        multi_isGameOver = true;
                    }
                    current = current->next;
                }
            }

#pragma omp task
            {
                if (multi_world[multi_Snake.head->y][multi_Snake.head->x] == '*') {
                    multi_addBody();
                    multi_generateFood();
                    (*score) = (*score) + 4;
                }
            }
#pragma omp taskwait
        }
    }
}

void multi_startSinglePlayer(int *score) {
    multi_isGameOver = false;
    multi_Snake.length = 0;
    multi_Snake.head = (multi_SnakeBody *)malloc(sizeof(multi_SnakeBody) * 100);
    multi_Snake.head->x = multi_snakeX;
    multi_Snake.head->y = multi_snakeY;
    multi_Snake.head->next = NULL;
    multi_Snake.tail = multi_Snake.head;

    multi_lastKey = 'd';

    srand(time(NULL));

    multi_addBody();
    multi_fillWorld();
    multi_generateFood();

    while (!multi_isGameOver) {
        system("cls");
        multi_fillWorld();
        multi_fillSnake();
        multi_printWorld(score);
        multi_readKey();
        multi_gameRules(score);
        Sleep(300);
    }
}