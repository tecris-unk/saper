//
// Created by intakvinta@gmail.com on 30.01.2025.
//

#include "functions.h"

void manage()
{
    random();
    int MODE = 1;
    while(1)
    {
        logo();
        getStart(&MODE);
        play(MODE);
    }
}
void random()
{
    unsigned seed = time(NULL);
    srand(seed);
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

// ----------------------------
void getStart(int* MODE)
{
    Cursor start;
    initCursor(&start);
    while(1)
    {
        menu();
        gotoxy(start.x-1, start.y);
        printf(">");

        start.yt = start.y;
        start.ch = _getch();
        if(start.ch == 80){start.y+=2;}
        if(start.ch == 72){start.y-=2;}
        if(start.ch == 13)
        {
            if(start.y == 1){return;}
            if(start.y == 3){info();}
            if(start.y == 5){getMode(MODE);}
            if(start.y == 7){exit(0);}
        }
        if(start.y > 7 || start.y < 1){start.y = start.yt;}
    }
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
    printf("quit");
}
void fout(char* fileName, size_t size)
{
    char buffer[size];
    FILE *fp = fopen(fileName, "r");
    if(fp)
    {
        (fgets(buffer, size, fp));
        printf("%s", buffer);
    }
    fclose(fp);
}
void info()
{
    system("cls");
    fout("info.txt", 303);
    printf("\nenter to open cell\nf\\F to make flag\npress enter to back");
    while(getchar()!='\n');
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
    if(MODE == 1){setColor(0, MODE);}
    printf("easy(1x score, small map)\n");
    if(MODE == 1){setColor(0, 15);}
    gotoxy(2, 3);
    if(MODE == 2){setColor(0, MODE);}
    printf("normal(2x score, medium map)\n");
    if(MODE == 2){setColor(0, 15);}
    gotoxy(2, 5);
    if(MODE == 3){setColor(0, MODE+1);}
    printf("hard(3x score, large map\n");
    if(MODE == 3){setColor(0, 15);}
    gotoxy(2, 7);
    printf("quit");
}
void initMap(Map* map, int MODE)
{
    (*map).MODE = MODE;
    (*map).flag = 0;
    (*map).opened = 0;
    (*map).size = MODE * 7;
    (*map).array = (int**)malloc((*map).size * sizeof(int*));
    (*map).mask = (int**)malloc((*map).size * sizeof(int*));
    if((*map).array == NULL || (*map).mask == NULL){printf("memory cant be allocated");}
    createMap(map);

    showMap(*map);
}
void initCursor(Cursor* cursor)
{
    (*cursor).x = 1;
    (*cursor).y = 1;
    (*cursor).xt = 1;
    (*cursor).yt = 1;
    gotoxy((*cursor).x<<1, (*cursor).y);
}

void freeMap(Map* map)
{
    for(int i = 0;i < (*map).size; ++i)
    {
        free((*map).array[i]);
        free((*map).mask[i]);
    }
    free((*map).array);
    free((*map).mask);
    (*map).size = 0;
}
void createMap(Map* map)
{
    for(int i = 0;i < (*map).size;++i)
    {
        (*map).array[i] = (int*)malloc((*map).size * sizeof(int));
        (*map).mask[i] = (int*)calloc((*map).size, sizeof(int));
        for(int j = 0;j < (*map).size;++j)
        {
            if(i == 0 || j == 0 || i == (*map).size-1 || j == (*map).size-1)
                (*map).array[i][j] = BORDER;
            else
                (*map).array[i][j] = EMPTY;
        }
    }
}
void coutChar(char output, int color)
{
    setColor(0, color);
    printf("%c ", output);
    setColor(0, 15);
}
void coutInt(int output, int color)
{
    setColor(0, color);
    printf("%d ", output);
    setColor(0, 15);
}
void showMap(Map map)
{
    system("cls");
    for(int i = 0;i < map.size;++i)
    {
        for(int j = 0;j < map.size;++j)
        {
            if(map.array[i][j] == BORDER)
                coutChar('#', 5);

            else if(map.mask[i][j] == EMPTY)
                coutChar('.', 15);

            else if(map.mask[i][j] == FLAG)
                coutChar('F', 10);

            else if(map.array[i][j] == EMPTY)
                printf("  ");

            else if(map.array[i][j] == MINE)
                coutChar('*', 15);

            else if(map.array[i][j] == 1)
                coutInt(map.array[i][j], 1);

            else if(map.array[i][j] == 2)
                coutInt(map.array[i][j], 3);

            else if(map.array[i][j] == 3)
                coutInt(map.array[i][j], 6);

            else if(map.array[i][j] == 4)
                coutInt(map.array[i][j], 4);

            else
                coutInt(map.array[i][j], 15);
        }
        printf("\n");
    }
    gotoxy(map.size<<1, 2);
    printf("MINES:%d", map.MODE * map.MODE * map.MODE * 4 - map.flag);
    gotoxy(map.size<<1, 4);
    printf("SCORE:%d", map.opened * map.MODE * 50);
}


void getMode(int* MODE)
{
    Cursor mode;
    initCursor(&mode);
    while(1)
    {
        modes(*MODE);
        gotoxy(mode.x-1, mode.y);
        printf(">");

        mode.yt = mode.y;
        mode.ch = _getch();
        if(mode.ch == 80){mode.y+=2;}
        if(mode.ch == 72){mode.y-=2;}
        if(mode.ch == 13)
        {
            if(mode.y == 1){*MODE = 1;}
            if(mode.y == 3){*MODE = 2;}
            if(mode.y == 5){*MODE = 3;}
            if(mode.y == 7){return;}
        }
        if(mode.y > 7 || mode.y < 1){mode.y = mode.yt;}
    }
}
// ----------------
void play(int MODE)
{
    Map map;
    initMap(&map, MODE);
    Cursor cursor;
    initCursor(&cursor);
    while(1)
    {
        cursor.xt = cursor.x;
        cursor.yt = cursor.y;
        cursor.ch = _getch();
        switch (cursor.ch) {
            case 77: cursor.x++;break;
            case 80: cursor.y++;break;
            case 75: cursor.x--;break;
            case 72: cursor.y--;break;
            case 13: if(map.mask[cursor.y][cursor.x] != FLAG){
                    if(!map.opened)
                        createMines(&map, 4 * MODE * MODE * MODE, cursor);
                    openCell(&map, cursor);
                    if(!map.size){return;}
                }break;
            case 63:
            case 102: makeFlag(&map, cursor); break;
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
            i = rand()%((*map).size-2) + 1, j = rand()%((*map).size-2)+1;
        }while((*map).array[i][j] == MINE || (abs(cursor.y-i)<=1 && abs(cursor.x-j)<=1));

        (*map).array[i][j] = MINE;
        for(int ii = -1; ii <= 1; ii++)
            for(int jj = -1;jj <= 1; jj++)
                if((*map).array[i + ii][j + jj] < MINE && (ii != 0 || jj != 0))
                    (*map).array[i + ii][j + jj]++;
    }
}
void openCell(Map* map, Cursor cursor)
{
    (*map).mask[cursor.y][cursor.x] = OPEN;
    if((*map).array[cursor.y][cursor.x] == EMPTY)
        openEmpty(map, cursor.x, cursor.y);

    showMap(*map);
    int numberOfCells = ((*map).size-2)*((*map).size-2);
    int numberOfMines = 4*(*map).MODE*(*map).MODE*(*map).MODE;
    if((*map).array[cursor.y][cursor.x] == MINE){
        endGame(0);
        freeMap(map);
    }
    else if(++(*map).opened == numberOfCells - numberOfMines){
        endGame(1);
        freeMap(map);
    }
}
void endGame(int end)
{
    gotoxy(42, 8);
    if(end)
        printf("Congratulations");
    else
        printf("GAME OVER!!");
    Sleep(2000);
}
void openEmpty(Map* map, int x, int y)
{
    for(int i = -1; i<=1; i++)
        for(int j = -1;j<=1; j++)
        {
            if((*map).array[y+i][x+j] == EMPTY && (i!=0||j!=0) && !(*map).mask[y+i][x+j]){
                (*map).mask[y+i][x+j] = OPEN;
                (*map).opened++;
                openEmpty(map,x+j, y+i);
            }
            if((*map).array[y+i][x+j] < MINE && (i!=0||j!=0) && !(*map).mask[y+i][x+j]){
                (*map).mask[y+i][x+j] = OPEN;
                (*map).opened++;
            }
        }
}
void makeFlag(Map* map, Cursor cursor)
{
    if((*map).mask[cursor.y][cursor.x] == EMPTY)
    {
        (*map).mask[cursor.y][cursor.x] = FLAG;
        (*map).flag++;
    }
    else if((*map).mask[cursor.y][cursor.x] == FLAG)
    {
        (*map).mask[cursor.y][cursor.x] = EMPTY;
        (*map).flag--;
    }
    showMap(*map);
}
