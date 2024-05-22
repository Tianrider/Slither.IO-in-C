#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char nama[100];
    int score;
    struct Player *next;
} Player;

// Function to add a new node to the linked list
void insertNode(Player **head, Player **tail, char *nama, int score) {
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newPlayer->nama, nama);
    newPlayer->score = score;
    newPlayer->next = NULL;

    // check for duplicate username
    if (*head != NULL) {
        Player *current = *head;
        while (current != NULL) {
            if (strcasecmp(current->nama, nama) == 0) {
                if (current->score < score) {
                    current->score = score;
                }
                return;
            }
            current = current->next;
        }
    }

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

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d", nama, &score);
        insertNode(head, tail, nama, score);
    }

    fclose(file);
}

// Function to write nodes to leaderboard.txt
void saveLeaderboard(Player *head) {
    FILE *file = fopen("leaderboard.txt", "w");
    Player *current = head;

    while (current != NULL) {
        fprintf(file, "%s,%d\n", current->nama, current->score);
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
    int score, i = 1;

    printf("%-3s |\t%-20s %s\n", "No", "Username", "Score");

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d", nama, &score);
        printf("%-3d |\t%-20s %d\n", i, nama, score);
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

    openLeaderboard(&head, &tail);
    insertNode(&head, &tail, nama, *score);
    sortLeaderboard(head);
    saveLeaderboard(head);

    // Cleanup linked list
    Player *current = head;
    while (current != NULL) {
        Player *temp = current;
        current = current->next;
        free(temp);
    }
}
