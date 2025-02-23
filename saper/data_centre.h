//
// Created by intak on 22.02.2025.
//

#ifndef SAPER_DATA_CENTRE_H
#define SAPER_DATA_CENTRE_H
#include "functions.h"
#define HASH_TABLE_SIZE 101
void loadHashTable(const char *filename, User* hashTable[]);
User *initUser(User* hashTable[]);
unsigned long hash(const char *str);
int addUser(User *hashTable[], const char *username, int usernameSize, const char *password, int passwordSize);
User *findUser(User *hashTable[], const char *username);
void freeHashTable(User *hashTable[]);
void leaderBoard(User* hashTable[]);
int changeUserScore(User *hashTable[], const char *username, int newScore);

#endif //SAPER_DATA_CENTRE_H
