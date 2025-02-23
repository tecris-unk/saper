//
// Created by intakvinta@gmail.com on 30.01.2025.
//

#ifndef SAPER_FUNCTIONS_H
#define SAPER_FUNCTIONS_H


#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "minesweeper_struct.h"
#include "data_centre.h"


#define BORDER 100
#define EMPTY 0
#define MINE 10
#define FLAG 30
#define OPEN 1
#define ENTER 13

enum ConsoleColor
{
    Black         = 0,
    Blue          = 1,
    Green         = 2,
    Cyan          = 3,
    Red           = 4,
    Magenta       = 5,
    Brown         = 6,
    LightGray     = 7,
    DarkGray      = 8,
    LightBlue     = 9,
    LightGreen    = 10,
    LightCyan     = 11,
    LightRed      = 12,
    LightMagenta  = 13,
    Yellow        = 14,
    White         = 15
};

void initGame(Game *game);
void random();
void gotoxy(short x, short y);
void logo();
void resize(char** array, int size);
void scanString(char **string, int *size);
int strSize(const char* str);
int isEqual(const char* str1, const char* str2);
void strCopy(char** firstStr, const char* secStr, int size);
//-------------
void startMenu(Game *game, User **hashTable);
void menu();
void fOut(char* fileName, size_t size);
void info();
void modes(int MODE);
void exitGame();
void getMode(int* MODE);
void consoleOut(int x, int y, int code);
void getCell(int cell);

void setColor(int background, int text);
void coutStr(char* output, int color);
void coutInt(int output, int color);

void createMap(Map* map);
void showMap(Map map, Game game);
void showStats(int size, Game game);
void initMap(Map* map, Game game);

void initCursor(Cursor* cursor);


void play(Game *game);

void freeMap(Map* map);
void openEmpty(Map* map, Game *game, int x, int y);
void endGame(int end, Game *game);
void openCell(Map* map, Cursor cursor, Game *game);
void makeFlag(Map* map, Cursor cursor, Game *game);
void createMines(Map* map, int mines, Cursor cursor);


#endif //SAPER_FUNCTIONS_H