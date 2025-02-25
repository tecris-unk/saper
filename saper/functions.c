//
// Created by intakvinta@gmail.com on 30.01.2025.
//
#include "functions.h"

void random()
{
    unsigned seed = time(NULL);
    srand(seed);
}
void initGame(Game *game)
{
    game->score = 0;
    game->flag = 0;
    game->opened = 0;
}
void logo()
{
    system("cls");
    gotoxy(42, 10);
    printf("Saper");
    Sleep(2000);
}
void gotoxy(short x, short y)
{
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void strCopy(char** firstStr, const char* secStr, int size)
{

    if(*firstStr != NULL)
    {
        free(*firstStr);
        *firstStr = NULL;
    }

    for(int i = 0; i < size; ++i)
    {
        resize(firstStr, i+1);
        (*firstStr)[i] = secStr[i];
    }

}
void coutString(char* string)
{
    for(int i = 0; string[i] != '\0'; ++i)
        printf("%c", string[i]);
}
void scanString(char **string, int *size) {
    *string = NULL;
    *size = 0;
    int c;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        (*size)++;
        char *temp = (char *)realloc(*string, sizeof(char) * (*size + 1));
        if (temp == NULL) {
            printf("memory cant be allocated");
            if (*string != NULL) {
                free(*string);
            }
            exit(1);
        } else {
            *string = temp;
            (*string)[i] = (char)c;
            (*string)[i+1] = '\0';
        }
        i++;
    }
    if (*string == NULL) {
        // Если ничего не было введено, выделяем 1 байт и ставим нуль-терминатор
        *string = (char *)malloc(sizeof(char));
        if (*string == NULL) {
            printf("memory cant be allocated\n");
            exit(1);
        }
        (*string)[0] = '\0';
    }
}
void resize(char** array, int size)
{
    char *temp = NULL;
    temp = (char*)realloc(*array, sizeof(temp) * (size+1));
    if(temp == NULL){
        printf("memory cant be allocated\n");
        free(temp);
        exit(1);
    }
    else{
        *array = (char*)temp;
        (*array)[size] = '\0';
    }
}
int isEqual(const char* str1, const char* str2)
{
    if(strSize(str1) != strSize(str2)){return 0;}

    for(int i = 0;i < strSize(str1); ++i)
    {
        if(str1[i] != str2[i]){return 0;}
    }
    return 1;
}
int strSize(const char* str)
{
    int i = 0;
    while(str[i] != '\0' && str[i] != EOF){i++;}
    return i;
}
// ----------------------------
void startMenu(Game *game, Tree *board, int* isEnd)
{
    initGame(game);
    Cursor start;
    initCursor(&start);
    menu();
    while(1)
    {
        consoleOut(start.x-1,  start.y, 50);
        start.yt = start.y;
        start.ch = _getch();
        switch(start.ch)
        {
            case 'w':
            case 'W':
            case 72 :
                start.y-=2;
                break;
            case 's':
            case 'S':
            case 80 :
                start.y+=2;
                break;
            case ENTER:
                if(start.y == 1){return;}
                if(start.y == 3){info();}
                if(start.y == 5){getMode(&game->mode);menu();}
                if(start.y == 7){
                    system("cls");
                    printLeaderboard(board);
                    printf("Press enter to continue\n");
                    while(getch() != ENTER);
                    system("cls");
                    menu();
                }
                if(start.y == 9){*isEnd = 1; return;}
                break;
        }
        if(start.y > 9 || start.y < 1){start.y = start.yt;}
        consoleOut(start.xt-1,  start.yt, 0);
    }
}
void consoleOut(int x, int y, int code)
{
    DWORD dw;
    COORD here;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    here.X = x;
    here.Y = y;

    char c = ' ';
    WriteConsoleOutputCharacter(hStdOut, &c, 1, here, &dw);
    gotoxy(x, y);
    getCell(code);
}

void menu()
{
    system("cls");
    gotoxy(2, 1);
    printf("play");
    gotoxy(2, 3);
    printf("info");
    gotoxy(2, 5);
    printf("modes");
    gotoxy(2, 7);
    printf("leaderboard");
    gotoxy(2, 9);
    printf("quit");
    gotoxy(0, 0);
}
void fOut(char* fileName, size_t size)
{
    char buffer[size];
    FILE *fp = fopen(fileName, "r");
    if(fp){
        fread(buffer,sizeof(char),size,fp);
        printf("%s", buffer);
    }
    else{
        printf("file cant be opened\npush enter to continue");
    }
    fclose(fp);
}
void info()
{
    system("cls");
    fOut("info.txt", 303);
    printf("\nenter to open cell\nf\\F to make flag\npress enter to back");
    while(getch()!=ENTER);
    menu();
}
void setColor(int background, int text)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void modes(int MODE)
{
    system("cls");

    gotoxy(2, 1);
    if(MODE == 1){setColor(Black, MODE);}
    printf("easy(1x score, small map)\n");
    setColor(Black, White);

    gotoxy(2, 3);
    if(MODE == 2){setColor(Black, MODE);}
    printf("normal(2x score, medium map)\n");
    setColor(Black, White);

    gotoxy(2, 5);
    if(MODE == 3){setColor(Black, MODE+1);}
    printf("hard(3x score, large map\n");
    setColor(Black, White);

    gotoxy(2, 7);
    printf("quit");
}
void exitGame()
{
    system("cls");
    printf(":(");
    Sleep(2000);
    exit(0);
}
void initMap(Map* map, Game game)
{
    map->size = game.mode * 7;
    map->array = (int**)malloc(map->size * sizeof(int*));
    map->mask = (int**)malloc(map->size * sizeof(int*));
    if(map->array == NULL || map->mask == NULL){
        printf("memory cant be allocated");
        exitGame();
    }
    createMap(map);
    showMap(*map, game);
}
void initCursor(Cursor* cursor)
{
    cursor->x = 1;
    cursor->y = 1;
    cursor->xt = 1;
    cursor->yt = 1;
    gotoxy(cursor->x * 2, cursor->y);
}

void freeMap(Map* map)
{
    for(int i = 0;i < map->size; ++i)
    {
        free(map->array[i]);
        free(map->mask[i]);
    }
    free(map->array);
    free(map->mask);
    map->size = 0;
}
void createMap(Map* map)
{
    for(int i = 0;i < map->size;++i)
    {
        map->array[i] = (int*)malloc(map->size * sizeof(int));
        map->mask[i] = (int*)calloc(map->size, sizeof(int));
        if(map->array[i] == NULL || map->mask[i] == NULL){
            printf("memory cant be allocated");
            exitGame();
        }
        for(int j = 0;j < map->size;++j)
        {
            if(i == 0 || j == 0 || i == map->size-1 || j == map->size-1)
                  map->array[i][j] = BORDER;
            else
                  map->array[i][j] = EMPTY;
        }
    }
}
void coutStr(char* output, int color)
{
    setColor(Black, color);
    printf("%s ", output);
    setColor(Black, White);
}
void coutInt(int output, int color)
{
    setColor(Black, color);
    printf("%d ", output);
    setColor(Black, White);
}
void getCell(int cell)
{
    if(cell == BORDER)
        coutStr("#", Magenta);

    else if(cell == EMPTY)
        printf("  ");

    else if(cell == MINE)
        coutStr("*", White);

    else if(cell == 1)
        coutInt(1, Blue);

    else if(cell == 2)
        coutInt(2, Cyan);

    else if(cell == 3)
        coutInt(3, Brown);

    else if(cell == 4)
        coutInt(4, LightRed);

    else if(cell == 5)
        coutInt(5, Red);

    else if(cell == 50)
        coutStr(">", Red);

    else if(cell == 51)
        coutStr("F", Green);

    else if(cell == 21)
        coutStr(".", White);
    else
        coutInt(cell, White);
}
void showMap(Map map, Game game)
{
    system("cls");
    for(int i = 0;i < map.size;++i)
    {
        for(int j = 0;j < map.size;++j)
        {
            if(map.array[i][j] != BORDER)
            {
                if(map.mask[i][j] == EMPTY)
                    coutStr(".", White);
                else if(map.mask[i][j] == FLAG)
                    coutStr("F", 10);
            }
            else getCell(map.array[i][j]);
        }
        printf("\n");
    }
    showStats(map.size, game);
}
void showStats(int size, Game game)
{
    gotoxy(size<<1, 2);
    int numberOfMines = game.mode * game.mode * game.mode * 4;
    if(numberOfMines - game.flag < 10){printf("MINES:00%d", game.mode * game.mode * game.mode * 4 - game.flag);}
    else if(numberOfMines - game.flag < 100){printf("MINES:0%d", game.mode * game.mode * game.mode * 4 - game.flag);}
    else{printf("MINES:%d", numberOfMines - game.flag);}

    gotoxy(size<<1, 4);
    game.score = game.opened * game.mode * 50;
    printf("SCORE:%d", game.score);
}
void getMode(int* MODE)
{
    Cursor mode;
    initCursor(&mode);
    modes(*MODE);
    while(1)
    {
        consoleOut(mode.x-1, mode.y, 50);
        int oldMode = *MODE;
        mode.yt = mode.y;
        mode.ch = _getch();
        switch(mode.ch)
        {
            case 'w':
            case 'W':
            case 72 :
                mode.y-=2;
                break;
            case 's':
            case 'S':
            case 80 :
                mode.y+=2;
                break;
            case ENTER:
                if(mode.y == 1){*MODE = 1;}
                if(mode.y == 3){*MODE = 2;}
                if(mode.y == 5){*MODE = 3;}
                if(mode.y == 7){return;}
                else if(oldMode!=*MODE){modes(*MODE);}
                break;
        }
        if(mode.y > 7 || mode.y < 1){mode.y = mode.yt;}
        consoleOut(mode.xt-1, mode.yt, 0);
    }
}
// ----------------
void play(Game *game)
{
    Map map;
    initMap(&map, *game);
    Cursor cursor;
    initCursor(&cursor);
    while(1)
    {
        cursor.xt = cursor.x;
        cursor.yt = cursor.y;
        cursor.ch = _getch();
        switch (cursor.ch) {
            case 'd':
            case 'D':
            case 77 :
                cursor.x++;break;
            case 's':
            case 'S':
            case  80:
                cursor.y++;break;
            case 'w':
            case 'W':
            case 72 :
                cursor.y--;break;
            case 'a':
            case 'A':
            case 75 :
                cursor.x--;break;
            case ENTER: if(map.mask[cursor.y][cursor.x] == EMPTY){
                    if(!game->opened)
                        createMines(&map, 4 * game->mode * game->mode * game->mode, cursor);
                    openCell(&map, cursor, game);
                    if(!map.size){return;}
                }break;
            case 'f':
            case 'F':
                makeFlag(&map, cursor, game); break;
        }
        if(map.array[cursor.x][cursor.y] == BORDER){
            cursor.x = cursor.xt;
            cursor.y = cursor.yt;
        }
        gotoxy(cursor.x<<1, cursor.y);
    }
}
void createMines(Map* map, int mines, Cursor cursor)
{
    int i, j;
    while(mines--)
    {
        do {
            i = rand() % ((*map).size - 2) + 1;
            j = rand() % ((*map).size - 2) + 1;
        } while(map->array[i][j] == MINE || (abs(cursor.y-i)<=1 && abs(cursor.x-j)<=1));

        map->array[i][j] = MINE;
        for(int ii = -1; ii <= 1; ii++)
            for(int jj = -1;jj <= 1; jj++)
                if(map->array[i + ii][j + jj] < MINE && (ii != 0 || jj != 0))
                    map->array[i + ii][j + jj]++;
    }
}
void openCell(Map* map, Cursor cursor, Game *game)
{
    map->mask[cursor.y][cursor.x] = OPEN;
    consoleOut(cursor.x<<1, cursor.y, map->array[cursor.y][cursor.x]);
    game->opened++;
    if(map->array[cursor.y][cursor.x] == EMPTY)
        openEmpty(map, game, cursor.x, cursor.y);

    showStats(map->size, *game);
    int numberOfCells = (map->size - 2) * (map->size - 2);
    int numberOfMines = 4 * game->mode * game->mode * game->mode;
    if(map->array[cursor.y][cursor.x] == MINE){
        endGame(0, game);
        freeMap(map);
    }
    else if(game->opened >= numberOfCells - numberOfMines){
        endGame(1, game);
        freeMap(map);
    }
}
void endGame(int end, Game *game)
{
    gotoxy(42, 8);

    if(end)
    {
        printf("Congratulations");
        game->score = game->score = game->opened * game->mode * 50;
    }
    else
    {
        printf("GAME OVER!!");
        game->score = game->score = game->opened * game->mode * 25;
    }

    Sleep(2000);
}
void openEmpty(Map* map, Game *game, int x, int y)
{
    for(int i = -1; i<=1; i++)
        for(int j = -1;j<=1; j++)
        {
            if((i!=0||j!=0) && map->array[y+i][x+j] < MINE && map->mask[y+i][x+j] == EMPTY) {
                game->opened++;
                consoleOut((x+j)<<1, y+i, map->array[y+i][x+j]);
                map->mask[y + i][x + j] = OPEN;
                if (map->array[y+i][x+j] == EMPTY) {
                openEmpty(map, game, x + j, y + i);
                }
            }
        }
}
void makeFlag(Map* map, Cursor cursor, Game *game)
{
    if(map->mask[cursor.y][cursor.x] == EMPTY)
    {
        map->mask[cursor.y][cursor.x] = FLAG;
        game->flag++;

    }
    else if(map->mask[cursor.y][cursor.x] == FLAG)
    {
        map->mask[cursor.y][cursor.x] = EMPTY;
        game->flag--;
    }
    else{return;}
    consoleOut(cursor.x<<1, cursor.y, map->mask[cursor.y][cursor.x]+21);
    showStats(map->size, *game);
}
