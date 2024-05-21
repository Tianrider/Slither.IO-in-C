#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char nama[100];
    int score;
    struct Player *next;
} Player;

Player *head = NULL, *tail = NULL;

// Fungsi untuk menambahkan node baru ke linked list
void insertNode(char *nama, int score) {
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    strcpy(newPlayer->nama, nama);
    newPlayer->score = score;
    newPlayer->next = NULL;

    if (head == NULL) {
        head = tail = newPlayer;
    } else {
        tail->next = newPlayer;
        tail = newPlayer;
    }
}

// Fungsi untuk mengurutkan linked list berdasarkan score dan nama
void sortLeaderboard() {
    Player *current, *index;
    char tempNama[50];
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

// Fungsi untuk membuka leaderboard.txt dan memasukkan data ke linked list
void openLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");

    if (file == NULL) {
        return;
    }

    char line[150];
    char nama[100];
    int score;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%d", nama, &score);
        insertNode(nama, score);
    }

    fclose(file);
}
// Fungsi untuk menulis node ke leaderboard.txt
void saveLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "w");
    Player *current = head;

    while (current != NULL) {
        fprintf(file, "%s,%d\n", current->nama, current->score);
        current = current->next;
    }

    fclose(file);
}

// Fungsi untuk menampilkan leaderboard
void showLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");

    if (file == NULL) {
        printf("                                             Leaderboard is empty!                                             \n");
        printf("===============================================================================================================\n");
        getch();
        return;
    }

    char nama[50];
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

// Fungsi untuk mengupdate leaderboard setiap kali game selesai (Singleplayer)
void leaderboard(char *nama, int *score) {
    Player *current = head;
    while (current != NULL) {
        Player *temp = current;
        current = current->next;
        free(temp);
    }

    head = tail = NULL;

    openLeaderboard();
    insertNode(nama, *score);
    sortLeaderboard();
    saveLeaderboard();
}