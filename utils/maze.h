#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include <stdint.h>

// The unit cell of the maze.
typedef struct {
    bool left_wall;
    bool right_wall;
    bool top_wall;
    bool bottom_wall;
    bool visited;
} unit_info_t;

// The maze
typedef struct {
    uint16_t start_x;
    uint16_t start_y;
    uint16_t end_x;
    uint16_t end_y;
    uint16_t rows;
    uint16_t cols;
    unit_info_t *units;
} maze_t;

/**
 * @brief           Unpack maze data from stdin.
 * @param[out] maze The maze data to be written in.
 */
void unpack_maze(maze_t* maze);

/**
 * @brief           Free the maze data.
 * @param[in] maze  The maze data to be free.
 */
 void free_maze(maze_t* maze);

 /**
  * @brief      Print the maze in ASCII.
  * @param[in]  The maze to be printed.
  */
  void print_maze_ASCII(maze_t* maze);
#endif
