#include "functions.h"

int main() {

    User *hashTable[HASH_TABLE_SIZE];
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    loadHashTable("userinfo.txt", hashTable);
    leaderBoard(hashTable);
    User *currUser = initUser(hashTable);

    random();
    Game game;
    game.mode = 1;
    while(1)
    {
        logo();
        startMenu(&game, hashTable);
        play(&game);
        currUser->score += game.score;
        changeUserScore(hashTable, currUser->username, currUser->score);
        system("cls");
    }
}