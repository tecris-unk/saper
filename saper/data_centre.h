//
// Created by intak on 22.02.2025.
//

#ifndef SAPER_DATA_CENTRE_H
#define SAPER_DATA_CENTRE_H
#include "functions.h"
#define HASH_TABLE_SIZE 101
Tree* loadHashTable(const char *filename, User* hashTable[], Tree *board);
User *initUser(User* hashTable[], Tree *board);
unsigned long hash(const char *str);
int addUser(User *hashTable[], const char *username, int usernameSize, const char *password, int passwordSize);
User *findUser(User *hashTable[], const char *username);
void freeHashTable(User *hashTable[]);
void leaderBoard(User* hashTable[]);
int changeUserScore(User *hashTable[], const char *username, int newScore);
void printLeaderboard(Tree *board);
Tree *addNode(Tree *board, int score, char* name);
void changeNode(Tree *board, char *name, int score);
void freeTree(Tree *board);
#endif //SAPER_DATA_CENTRE_H
