#include "maze.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void unpack_maze(maze_t* maze) {
    // 2 bytes start point x; 2 bytes start point y;
    fread(&maze->start_x, 2, 1, stdin);
    fread(&maze->start_y, 2, 1, stdin);
    // 2 bytes end point x; 2 bytes end point y;
    fread(&maze->end_x, 2, 1, stdin);
    fread(&maze->end_y, 2, 1, stdin);
    // 2 bytes rows; 2 bytes cols;
    fread(&maze->rows, 2, 1, stdin);
    fread(&maze->cols, 2, 1, stdin);
    // malloc rows * cols units.
    int len = maze->rows * maze->cols;
    maze->units = malloc(len * sizeof(unit_info_t));
    for (int i = 0; i < len; ++i) {
        static uint8_t temp;
        fread(&temp, 1, 1, stdin);
        maze->units[i].left_wall = (bool)(temp & 0x80);
        maze->units[i].right_wall = (bool)(temp & 0x40);
        maze->units[i].top_wall = (bool)(temp & 0x20);
        maze->units[i].bottom_wall = (bool)(temp & 0x10);
        maze->units[i].visited = false;
        ++i;
        if (i < len) {
            maze->units[i].left_wall = (bool)(temp & 0x08);
            maze->units[i].right_wall = (bool)(temp & 0x04);
            maze->units[i].top_wall = (bool)(temp & 0x02);
            maze->units[i].bottom_wall = (bool)(temp & 0x01);
            maze->units[i].visited = false;
        }
    }
}

void free_maze(maze_t *maze) {
    free(maze->units);
    maze->units = NULL;
    free(maze);
}

void print_maze_ASCII(maze_t *maze) {
    for (int c = 0; c < maze->cols; ++c) {
        fprintf(stdout, " _");
    }
    printf(" *\n");
    for (int r = 0; r < maze->rows; ++r) {
        printf("|");
        for (int c = 0; c < maze->cols; ++c) {
            int i = r * maze->cols + c;
            fprintf(stdout ,"%c%c", (maze->units[i].bottom_wall? '_' : ' '), maze->units[i].right_wall? '|' : ' ');
        }
        fprintf(stdout ,"*\n");
    }
}
