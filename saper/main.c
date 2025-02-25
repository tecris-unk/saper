#include "functions.h"

int main() {
    random();

    User *hashTable[HASH_TABLE_SIZE];
    Tree *board = NULL;
    board = loadHashTable("userinfo.txt", hashTable, board);
    int isRegistered = 0;
    printf("Would you like to register / log in ?\nprintf y/n: ");

    User *currUser;
    int ch = getch();
    rewind(stdin);
    if(ch == 'y' || ch == 'Y')
    {
        currUser = initUser(hashTable, board);
        isRegistered = 1;
    }

    Game game;
    game.mode = 1;

    while(1)
    {
        logo();
        int isEnd = 0;
        startMenu(&game, board, &isEnd);
        if(!isEnd){play(&game);}
        if(isRegistered == 1){
            currUser->score += game.score;
            changeNode(board, currUser->username, currUser->score);
        }

        system("cls");

        printf("Would you like to continue play?\nprint y / n: ");
        ch = getchar();
        rewind(stdin);
        if(ch == 'n' || ch == 'N'){
            if(isRegistered == 1)
            {
                changeUserScore(hashTable, currUser->username, currUser->score);
            }
            freeHashTable(hashTable);
            freeTree(board);
            return 0;
        }
    }
}