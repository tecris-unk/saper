//
// Created by intakvinta@gmail.com on 30.01.2025.
//

#ifndef SAPER_FUNCTIONS_H
#define SAPER_FUNCTIONS_H


#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "mineswepeer_struct.h"

#define BORDER 100
#define EMPTY 0
#define MINE 10
#define FLAG 2
#define OPEN 1

void manage();

void random();
void gotoxy(short x, short y);
void logo();
//-------------
void getStart(int* MODE);
void menu();
void fout(char* fileName, size_t size);
void info();
void modes(int MODE);
void getMode(int* MODE);

void setColor(int background, int text);
void coutChar(char output, int color);
void coutInt(int output, int color);

void createMap(Map* map);
void showMap(Map map);
void initMap(Map* map, int MODE);

void initCursor(Cursor* cursor);


void play(int MODE);

void freeMap(Map* map);
void openEmpty(Map* map, int x, int y);
void endGame(int end);
void openCell(Map* map, Cursor cursor);
void makeFlag(Map* map, Cursor cursor);
void createMines(Map* map, int mines, Cursor cursor);



#endif //SAPER_FUNCTIONS_H