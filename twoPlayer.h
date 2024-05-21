#define rows 20
#define cols 40

int winner = 0;

char world[cols][rows];
char lastKeyOne = 'w';
char lastKeyTwo = 'i';

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

bool isGameOver = false;

struct Snake SnakeOne;
struct Snake SnakeTwo;

int playerOneScore = 0;
int playerTwoScore = 0;

void printWorld() {
    int i;
    printf("%-10s: %-5d %-10s: %-5d\n", "Player 1 Score", playerOneScore, "Player 2 Score", playerTwoScore);
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

void fillWorld() {
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

void fillSnake() {
    SnakeBody *current = SnakeOne.head;
    while (current != NULL) {
        world[current->x][current->y] = 'o';
        current = current->next;
    }
    current = SnakeTwo.head;
    while (current != NULL) {
        world[current->x][current->y] = 'x';
        current = current->next;
    }
}

void moveSnake(int snake, int x, int y) {
    struct Snake *currentSnake;
    if (snake == 0) {
        currentSnake = &SnakeOne;
    } else {
        currentSnake = &SnakeTwo;
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

void addBody(struct Snake *snake) {
    SnakeBody *newBody = (SnakeBody *)malloc(sizeof(SnakeBody));
    newBody->x = snake->tail->x;
    newBody->y = snake->tail->y;
    newBody->next = NULL;
    snake->tail->next = newBody;
    snake->tail = newBody;
    snake->length++;
}

void readKeyOne() {
    char key;

    if (kbhit()) {
        key = getch();
    } else {
        key = lastKeyOne;
    }

    if (key == 'i' || key == 'k' || key == 'j' || key == 'l') {
        lastKeyTwo = key;
    } else {
        lastKeyOne = key;
    }

    switch (lastKeyOne) {
    case 'w':
        moveSnake(0, 0, -1);
        break;
    case 's':
        moveSnake(0, 0, 1);
        break;
    case 'a':
        moveSnake(0, -1, 0);
        break;
    case 'd':
        moveSnake(0, 1, 0);
        break;
    default:
        break;
    }

    switch (lastKeyTwo) {
    case 'i':
        moveSnake(1, 0, -1);
        break;
    case 'k':
        moveSnake(1, 0, 1);
        break;
    case 'j':
        moveSnake(1, -1, 0);
        break;
    case 'l':
        moveSnake(1, 1, 0);
        break;
    default:
        break;
    }
}

void generateFood() {
    int x = rand() % (cols - 2) + 1;
    int y = rand() % (rows - 2) + 1;

    if (world[x][y] == ' ') {
        world[x][y] = '*';
    } else {
        generateFood();
    }
}

void checkCollision() {
    if (SnakeOne.head->x == 0 || SnakeOne.head->x == cols - 1 || SnakeOne.head->y == 0 || SnakeOne.head->y == rows - 1) {
        isGameOver = true;
        winner = 2;
    }

    if (SnakeTwo.head->x == 0 || SnakeTwo.head->x == cols - 1 || SnakeTwo.head->y == 0 || SnakeTwo.head->y == rows - 1) {
        isGameOver = true;
        winner = 1;
    }

    SnakeBody *current = SnakeOne.head->next;
    while (current != NULL) {
        if (current->x == SnakeOne.head->x && current->y == SnakeOne.head->y) {
            isGameOver = true;
            winner = 2;
        }
        current = current->next;
    }

    current = SnakeTwo.head->next;
    while (current != NULL) {
        if (current->x == SnakeTwo.head->x && current->y == SnakeTwo.head->y) {
            isGameOver = true;
            winner = 1;
        }
        current = current->next;
    }

    // check if player 1 eats player 2
    current = SnakeTwo.head;
    while (current != NULL) {
        if (current->x == SnakeOne.head->x && current->y == SnakeOne.head->y) {
            isGameOver = true;
            winner = 2;
        }
        current = current->next;
    }

    // check if player 2 eats player 1
    current = SnakeOne.head;
    while (current != NULL) {
        if (current->x == SnakeTwo.head->x && current->y == SnakeTwo.head->y) {
            isGameOver = true;
            winner = 1;
        }
        current = current->next;
    }

    // check food
    if (world[SnakeOne.head->x][SnakeOne.head->y] == '*') {
        playerOneScore += 4;
        addBody(&SnakeOne);
        generateFood();
    }

    if (world[SnakeTwo.head->x][SnakeTwo.head->y] == '*') {
        playerTwoScore += 4;
        addBody(&SnakeTwo);
        generateFood();
    }
}

void startTwoPlayer() {
    isGameOver = false;
    playerOneScore = 0;
    playerTwoScore = 0;

    srand(time(NULL));
    SnakeOne.length = 1;
    SnakeOne.head = (SnakeBody *)malloc(sizeof(SnakeBody));
    SnakeOne.head->x = 10;
    SnakeOne.head->y = 10;
    SnakeOne.head->next = NULL;
    SnakeOne.tail = SnakeOne.head;

    SnakeTwo.length = 1;
    SnakeTwo.head = (SnakeBody *)malloc(sizeof(SnakeBody));
    SnakeTwo.head->x = 30;
    SnakeTwo.head->y = 10;
    SnakeTwo.head->next = NULL;
    SnakeTwo.tail = SnakeTwo.head;

    world[10][10] = 'o';
    world[30][10] = 'x';

    fillWorld();
    generateFood();
    generateFood();

    while (!isGameOver) {
        fillWorld();
        fillSnake();
        printWorld();
        readKeyOne();
        // readKeyTwo();
        checkCollision();
        Sleep(300);
        system("cls");
    }

    system("cls");
    if (winner == 1) {
        printPlayerOneWin();
    } else {
        printPlayerTwoWin();
    }
}