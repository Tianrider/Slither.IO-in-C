#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char nama[100];
    int score;
    int gameCount;
    struct Player *next;
} Player;

// Function to add a new node to the linked list
void insertNode(Player **head, Player **tail, char *nama, int score, int gameCount) {
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newPlayer->nama, nama);
    newPlayer->score = score;
    newPlayer->gameCount = gameCount;
    newPlayer->next = NULL;

    if (*head == NULL) {
        *head = *tail = newPlayer;
    } else {
        (*tail)->next = newPlayer;
        *tail = newPlayer;
    }
}

// Function to sort the linked list by score and name
void sortLeaderboard(Player *head) {
    Player *current, *index;
    char tempNama[100];
    int tempScore;

    if (head == NULL) {
        return;
    }

    for (current = head; current != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->score < index->score ||
                (current->score == index->score && strcasecmp(current->nama, index->nama) > 0)) {
                tempScore = current->score;
                current->score = index->score;
                index->score = tempScore;

                strcpy(tempNama, current->nama);
                strcpy(current->nama, index->nama);
                strcpy(index->nama, tempNama);
            }
        }
    }
}

// Function to open leaderboard.txt and insert data into the linked list
void openLeaderboard(Player **head, Player **tail) {
    FILE *file = fopen("leaderboard.txt", "r");

    if (file == NULL) {
        return;
    }

    char line[150];
    char nama[100];
    int score;
    int gameCount;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d,%d", nama, &score, &gameCount);
        insertNode(head, tail, nama, score, gameCount);
    }

    fclose(file);
}

// Function to write nodes to leaderboard.txt
void saveLeaderboard(Player *head) {
    FILE *file = fopen("leaderboard.txt", "w");
    Player *current = head;

    while (current != NULL) {
        fprintf(file, "%s,%d,%d\n", current->nama, current->score, current->gameCount);
        current = current->next;
    }

    fclose(file);
}

// Function to display the leaderboard
void showLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");

    if (file == NULL) {
        printf("                                             Leaderboard is empty!                                             \n");
        printf("===============================================================================================================\n");
        getch();
        return;
    }

    char nama[100];
    int score, i = 1, gameCount;

    printf("%-3s |\t%-20s %-5s %s\n", "No", "Username", "Score", "Count");

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d, %d", nama, &score, &gameCount);
        printf("%-3d |\t%-20s %-5d %d\n", i, nama, score, gameCount);
        i++;
    }

    printf("===============================================================================================================\n");

    fclose(file);
    getch();
}

// check for existing user
int checkUser(char *nama) {
    FILE *file = fopen("leaderboard.txt", "r");

    if (file == NULL) {
        return 0;
    }

    char line[150];
    char username[100];
    int score;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d", username, &score);
        if (strcasecmp(username, nama) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Function to update the leaderboard after each game (Singleplayer)
void leaderboard(char *nama, int *score) {
    Player *head = NULL, *tail = NULL;

    int returningPlayer = 0;

    openLeaderboard(&head, &tail);
    Player *current = head;
    while (current != NULL) {
        if (strcasecmp(current->nama, nama) == 0) {
            current->score = *score;
            current->gameCount++;
            returningPlayer = 1;
            break;
        }
        current = current->next;
    }

    if (returningPlayer == 0) {
        insertNode(&head, &tail, nama, *score, 1);
    }

    sortLeaderboard(head);
    saveLeaderboard(head);

    // Cleanup linked list
    current = head;
    while (current != NULL) {
        Player *temp = current;
        current = current->next;
        free(temp);
    }
}
