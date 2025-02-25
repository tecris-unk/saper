//
// Created by intak on 22.02.2025.
//

#include "data_centre.h"
Tree* loadHashTable(const char *filename, User* hashTable[], Tree *board)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("file is clear\n");
        return NULL;
    }

    char *username = (char*)malloc(50 * sizeof(char));
    char *password = (char*)malloc(50 * sizeof(char));
    if(username==NULL||password == NULL){printf("malloc error");exit(1);}
    int score;

    while (fscanf(fp, "%49s %49s %d\n", username, password, &score) == 3) {

        unsigned long index = hash(username);
        User *newUser = (User *)malloc(sizeof(User));
        if (newUser == NULL) {
            perror("malloc failed");
            fclose(fp);
            return NULL;
        }

        strCopy(&newUser->username, username, strSize(username));
        strCopy(&newUser->password, password, strSize(password));
        newUser->score = score;
        newUser->next = NULL;

        board = addNode(board, score, newUser->username);

        if (hashTable[index] == NULL) {
            hashTable[index] = newUser;
        }
        else {
            newUser->next = hashTable[index];
            hashTable[index] = newUser;
        }
    }
    fclose(fp);

    return board;
}
User *initUser(User* hashTable[], Tree *board)
{
    printf("\n\nEnter your username\n");
    while(1)
    {
        char* username = NULL;
        int usernameSize = 0;
        while(usernameSize < 5)
        {
            scanString(&username, &usernameSize);
            if(usernameSize < 5)
                printf("Username must be bigger than 4 characters! Try again\n");
        }

        User *currUser = findUser(hashTable, username);
        if(currUser == NULL)
        {
            printf("There is not this user, would you like to register with this name ?(y/n)\n");
            int ch = getchar();
            rewind(stdin);
            if(ch == 'y'){
                char* password = NULL;
                int passwordSize = 0;
                printf("enter password: ");
                while(passwordSize < 3) {
                    scanString(&password, &passwordSize);
                    if(passwordSize < 3)
                        printf("Password must be bigger than 3 characters! Try again\n");
                }
                if(!addUser(hashTable, username, usernameSize, password, passwordSize)){
                    printf("ERROR");
                    exitGame();
                }
                addNode(board, 0, username);
                printf("Your account successfully created\n");
                Sleep(2000);
                return findUser(hashTable, username);
            }
            else{
                printf("Try to enter your name again!\n");
            }
        }
        else{
            printf("enter password or leave!!\n");
            int attempts = 3;
            while(attempts-->0)
            {
                char* password;
                int passwordSize;
                scanString(&password, &passwordSize);
                if(isEqual(currUser->password, password)){
                    printf("You successfully logged in\n");
                    Sleep(2000);
                    return currUser;
                }
                    printf("try again!! %d attempts left\n", attempts);
            }
            printf("ooops, try to log in another time!\n");
        }
    }

}

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = (int)*str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % HASH_TABLE_SIZE;
}


int addUser(User *hashTable[], const char *username, int usernameSize, const char *password, int passwordSize)
{
    unsigned long index = hash(username);

    User *newUser = (User *)malloc(sizeof(User));
    if (newUser == NULL) {
        perror("malloc failed");
        return 0;
    }
    strCopy(&newUser->username, username, usernameSize);
    strCopy(&newUser->password, password, passwordSize);
    newUser->score = 0;
    newUser->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newUser;
    } else {
        newUser->next = hashTable[index];
        hashTable[index] = newUser;
    }
    FILE *f = fopen("userinfo.txt", "a+");
    if(f == NULL)
    {
        printf("cant open file\n");
    }
    else{
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User *currentUser = hashTable[i];
        while (currentUser != NULL) {
            fprintf(f, "%s %s %d\n", currentUser->username, currentUser->password, currentUser->score); // Записываем score
            currentUser = currentUser->next;
        }
    }
    }
        fclose(f);
    return 1;
}

User *findUser(User **hashTable, const char *username)
{
    unsigned long index = hash(username);
    User *currentUser = hashTable[index];

    while (currentUser != NULL) {
        if (isEqual(currentUser->username, username)) {
            return currentUser;
        }
        currentUser = currentUser->next;
    }
    return NULL;
}

int changeUserScore(User *hashTable[], const char *username, int newScore)
{
    User *userToUpdate = findUser(hashTable, username);

    if (userToUpdate != NULL) {
        userToUpdate->score = newScore;

        FILE *f = fopen("userinfo.txt", "r+");
        if (f == NULL) {
            perror("Cant open file");
            return 0;
        }

        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            User *currentUser = hashTable[i];
            while (currentUser != NULL) {
                fprintf(f, "%s %s %d\n", currentUser->username, currentUser->password, currentUser->score);
                currentUser = currentUser->next;
            }
        }

        fclose(f);
        return 1;
    } else {
        printf("User %s not found.\n", username);
        return 0;
    }
}
void freeHashTable(User *hashTable[])
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User *currentUser = hashTable[i];
        while (currentUser != NULL) {
            User *temp = currentUser;
            currentUser = currentUser->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}
void printLeaderboard(Tree *board)
{
     if(board != NULL){
         printLeaderboard(board->left);
         coutString(board->name);
         printf(": %d\n", board->points);
         printLeaderboard(board->right);
     }
}
Tree *addNode(Tree *board, int score, char* name)
{
     if(board == NULL)
     {
         board = (Tree*)malloc(sizeof(Tree));
         if(board == NULL)
         {
             printf("tree is trash\n");
             exit(1);
         }
         board->left = NULL;
         board->right = NULL;
         board->points = score;
         strCopy(&board->name, name, strSize(name));
     }
     else{
         if(score  >  board->points){
             board->left = addNode(board->left, score, name);
         }
         else{
             board->right = addNode(board->right, score, name);
         }
     }

     return board;
}
void changeNode(Tree *board, char *name, int score)
{
    if(board != NULL)
    {
        if(isEqual(board->name, name) == 1){
            board->points = score;
            return;
        }
        else{
            changeNode(board->left, name, score);
            changeNode(board->right, name, score);
        }
    }
}
void freeTree(Tree *board)
{
        if (board != NULL)
        {
            freeTree(board->left);
            freeTree(board->right);
            free(board);
        }
}