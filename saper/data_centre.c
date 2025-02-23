//
// Created by intak on 22.02.2025.
//

#include "data_centre.h"
void loadHashTable(const char *filename, User* hashTable[])
{
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("file is clear\n");
        return;
    }

    char *username = (char*)malloc(50 * sizeof(char));
    char *password = (char*)malloc(50 * sizeof(char));
    if(username==NULL||password == NULL){printf("malloc error");exit(1);}
    int score; // Добавлено для чтения score

    while (fscanf(fp, "%49s %49s %d\n", username, password, &score) == 3) {

        unsigned long index = hash(username);
        User *newUser = (User *)malloc(sizeof(User));
        if (newUser == NULL) {
            perror("malloc failed");
            fclose(fp); // Закрываем файл при ошибке
            return;
        }
        newUser->nameSize = strSize(username);
        strCopy(&newUser->username, username, newUser->nameSize);
        newUser->passSize = strSize(password);
        strCopy(&newUser->password, password, newUser->passSize);
        newUser->score = score;
        newUser->next = NULL;

        if (hashTable[index] == NULL) {
            hashTable[index] = newUser;
        }
        else {
            newUser->next = hashTable[index];
            hashTable[index] = newUser;
        }
    }
    fclose(fp);
}
User *initUser(User* hashTable[])
{
    printf("Enter your username\n");
    while(1)
    {
        char* username = NULL;
        int usernameSize = 0;
        scanString(&username, &usernameSize);
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
                scanString(&password, &passwordSize);

                if(!addUser(hashTable, username, usernameSize, password, passwordSize)){
                    printf("ERROR");
                    exitGame();
                }
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
            while(attempts>0)
            {
                char* password;
                int passwordSize;
                scanString(&password, &passwordSize);
                if(isEqual(currUser->password, password)){
                    printf("You successfully logged in\n");
                    return currUser;
                }
                else{
                    printf("try again!! %d attempts left\n", attempts--);
                }
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
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

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

    newUser->nameSize = usernameSize;
    strCopy(&newUser->username, username, newUser->nameSize);
    newUser->passSize = passwordSize;
    strCopy(&newUser->password, password, newUser->passSize);
    newUser->score = 0;
    newUser->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newUser;
    } else {
        newUser->next = hashTable[index];
        hashTable[index] = newUser;
    }
    FILE *f = fopen("userinfo.txt", "r+");
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
            return currentUser; // Пользователь найден
        }
        currentUser = currentUser->next;
    }

    return NULL;
}
void leaderBoard(User* hashTable[])
{
    system("cls");
    printf("Scores of all users:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User *currUser = hashTable[i];
        while (currUser != NULL) {
            printf("Username: %s, Score: %d\n", currUser->username, currUser->score);
            currUser = currUser->next;
        }
    }
    printf("print enter to continue\n");
    while(getch()!=ENTER);
}
int changeUserScore(User *hashTable[], const char *username, int newScore)
{
    User *userToUpdate = findUser(hashTable, username);

    if (userToUpdate != NULL) {
        userToUpdate->score = newScore;

        FILE *f = fopen("userinfo.txt", "r+"); // Открываем для *перезаписи*
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
        return 1; // Успешно
    } else {
        printf("User %s not found.\n", username);
        return 0; // Пользователь не найден
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
