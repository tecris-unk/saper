//
// Created by intak on 31.01.2025.
//

#ifndef SAPER_MINESWEPEER_STRUCT_H
#define SAPER_MINESWEPEER_STRUCT_H

typedef struct {
    int size;
    int opened;
    int flag;
    int MODE;
    int **array;
    int **mask;
}Map;
typedef struct {
    int x;
    int y;
    int xt;
    int yt;
    int ch;
}Cursor;

#endif //SAPER_MINESWEPEER_STRUCT_H
