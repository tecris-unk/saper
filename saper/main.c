#include <stdio.h>
#include <windows.h>
#include <conio.h>
const int BORDER = 100;
const int EMPTY = 0;
const int MINE = 10;
const int FLAG = 2;
void setColor(int background, int text)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void gotoxy(short x, short y)
{
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void logo()
{
    gotoxy(40, 10);
    printf("Saper");
    Sleep(2000);
    system("cls");
}
struct Matrix
{
    int size;
    int** array;
    int** mask;
};

void createMatrix(int*** array, int*** mask, int size)
{
    for(int i = 0;i < size;++i)
    {
        (*array)[i] = (int*)malloc(size * sizeof(int));
        (*mask)[i] = (int*)calloc(size, sizeof(int));
        for(int j = 0;j < size;++j)
        {
            if(i == 0 || j == 0 || i == size-1 || j == size-1)
                (*array)[i][j] = BORDER;
            else
                (*array)[i][j] = EMPTY;
        }
    }
}
void showMatrix(int*** array, int*** mask, int size)
{
    system("cls");
    for(int i = 0;i < size;++i)
    {
        for(int j = 0;j < size;++j)
        {
            if((*array)[i][j] == BORDER)
            {
                setColor(0, 5);
                printf("#");
                setColor(0, 15);
            }
            else if((*mask)[i][j] == EMPTY){printf(".");}
            else if((*mask)[i][j] == FLAG)
            {
                setColor(0, 10);
                printf("F");
                setColor(0, 15);
            }
            else if((*array)[i][j] == EMPTY){printf(" ");}
            else if((*array)[i][j] == MINE){printf("*");}
            else if((*array)[i][j] == 1)
            {
                setColor(0, 1);
                printf("%d", (*array)[i][j]);
                setColor(0, 15);
            }
            else if((*array)[i][j] == 2)
            {
                setColor(0, 3);
                printf("%d", (*array)[i][j]);
                setColor(0, 15);
            }
            else if((*array)[i][j] == 3)
            {
                setColor(0, 6);
                printf("%d", (*array)[i][j]);
                setColor(0, 15);
            }
            else if((*array)[i][j] == 4)
            {
                setColor(0, 4);
                printf("%d", (*array)[i][j]);
                setColor(0, 15);
            }

        }
        printf("\n");
    }
}
void createMines(int*** array, int size, int mines)
{
    if(mines >= (size-2)*(size-2)){printf("too much mines!!!");return;}
    int i, j;
    while(mines-->0)
    {
        do {
            i = rand()%(size-2) + 1, j = rand()%(size-2)+1;
        }while((*array)[i][j] == MINE);
        (*array)[i][j] = MINE;
        for(int ii = -1; ii<=1; ii++)
        {
            for(int jj = -1;jj<=1; jj++)
            {
                if((*array)[i+ii][j+jj]<MINE && (ii!=0||jj!=0)){(*array)[i+ii][j+jj]++;}
            }
        }
    }
}
void openEmpty(int*** array, int*** mask, int x, int y)
{
    for(int i = -1; i<=1; i++)
    {
        for(int j = -1;j<=1; j++)
        {
            if((*array)[y+i][x+j] == EMPTY && (i!=0||j!=0) && !(*mask)[y+i][x+j]){
                (*mask)[y+i][x+j] = 1;
                openEmpty(array, mask,  x+j, y+i);
            }
            if((*array)[y+i][x+j] < MINE && (i!=0||j!=0) && !(*mask)[y+i][x+j]){
                (*mask)[y+i][x+j] = 1;
            }
        }
    }
}
int main(void) {
   logo();

    struct Matrix matrix;
    matrix.size = 10;
    matrix.array = (int**)malloc(matrix.size * sizeof(int*));
    matrix.mask = (int**)malloc(matrix.size * sizeof(int*));
    if(matrix.array == NULL){printf("memory cant be allocated");}
    createMatrix(&matrix.array, &matrix.mask, matrix.size);
    createMines(&matrix.array, matrix.size, 10);
    showMatrix(&matrix.array, &matrix.mask, matrix.size);

    int ch;

    int x = 1, y = 1;
    int tx = 1, ty = 1;

    gotoxy(x, y);
    while(1)
    {
        tx = x;
        ty = y;
       ch = _getch();
       if(ch == 77){x++;}
       if(ch == 80){y++;}
       if(ch == 75){x--;}
       if(ch == 72){y--;}
       if(ch == 13){
           matrix.mask[y][x] = 1;
           if(matrix.array[y][x] == EMPTY)
           {
               openEmpty(&matrix.array, &matrix.mask, x, y);
           }
           showMatrix(&matrix.array, &matrix.mask, matrix.size);
           if(matrix.array[y][x] == MINE){
               gotoxy(40, 9);
               printf("GAME OVER!!");
               Sleep(2000);
               free(matrix.array);
               free(matrix.mask);
               return 0;
           }
       }
       if((ch == 63 || ch == 102) && matrix.mask[y][x] != 2){
           matrix.mask[y][x] = 2;
           showMatrix(&matrix.array, &matrix.mask, matrix.size);
       }
       else if(ch == 63 || ch == 102)
       {
           matrix.mask[y][x] = 0;
           showMatrix(&matrix.array, &matrix.mask, matrix.size);
       }
       if(matrix.array[x][y] == BORDER){
           x = tx;
           y = ty;
       }
        gotoxy(x, y);
    }
}
