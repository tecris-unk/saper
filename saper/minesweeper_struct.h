//
// Created by intak on 31.01.2025.
//

#ifndef SAPER_MINESWEEPER_STRUCT_H
#define SAPER_MINESWEEPER_STRUCT_H

typedef struct {
    int size;
    int **array;
    int **mask;
}Map;
typedef struct {
    int opened;
    int flag;
    int mode;
    int score;
}Game;
typedef struct {
    int x;
    int y;
    int xt;
    int yt;
    int ch;
}Cursor;
typedef struct User {
    char *username;
    char *password;
    int score;
    struct User *next;
} User;
typedef struct Tree{
    int points;
    char *name;
    struct Tree *left;
    struct Tree *right;
}Tree;
#endif //SAPER_MINESWEEPER_STRUCT_H
