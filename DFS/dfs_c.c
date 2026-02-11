#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../utils/maze.h"
#include "../utils/stack.h"

void dfs(maze_t *maze);
int compare_direction(const void *a, const void *b);
int compare_direction_desc(const void *a, const void *b);
bool encounter_wall(int dx, int dy, uint16_t current[2], maze_t *maze);
bool find_next(uint16_t current[2], uint16_t next[2], maze_t *maze);
void goto_next(uint16_t next[2], maze_t *maze);

int main() {
    printf("Using DFS in C language.\n");
    fflush(stdout);
    maze_t *maze = malloc(sizeof(*maze));
    unpack_maze(maze);
    printf("Unpacked maze data.\n");
    printf("The maze has %d rows, %d columns.\n", maze->rows, maze->cols);
    printf("Start from %d, %d to %d, %d\n", maze->start_x, maze->start_y, maze->end_x, maze->end_y);
    fflush(stdout);
    print_maze_ASCII(maze);
    dfs(maze);
    free_maze(maze);
}

void dfs(maze_t *maze) {
    uint16_t *current = malloc(2 * sizeof(uint16_t));
    current[0] = maze->start_x;
    current[1] = maze->start_y;
    maze->units[current[0] + current[1] * maze->cols].visited = true;
    bstack_t *stack = malloc(sizeof(bstack_t));
    stack_init(stack, maze->rows * maze->cols);
    stack_push(stack, current);
    while (!stack_empty(stack)) {
        uint16_t *next = malloc(2 * sizeof(uint16_t));
        void *t;
        stack_peek(stack, &t);
        current = (uint16_t *)t;
        printf("current: %d, %d\n", current[0], current[1]);
        if (current[0] == maze->end_x && current[1] == maze->end_y) break;
        if (find_next(current, next, maze)) {
            // Go to next;
            goto_next(next, maze);
            stack_push(stack, next);
        } else {
            stack_pop(stack, &t);
        }
    }
    printf("minimal steps: %d\n", stack->top);
    stack_free(stack);
}

int compare_direction(const void *a, const void *b) {
    int *pa = *(int **)a;
    int *pb = *(int **)b;
    int ia = pa[2];
    int ib = pb[2];
    return (ia > ib) - (ia < ib);
}
int compare_direction_desc(const void *a, const void *b){
    return compare_direction(b, a);
}
bool encounter_wall(int dx, int dy, uint16_t current[2], maze_t *maze) {
    int direction;
    if (dx == -1) direction = 0;
    if (dx == 1) direction = 1;
    if (dy == -1) direction = 2;
    if (dy == 1) direction = 3;
    switch (direction) {
        case 0: return maze->units[current[0] + current[1] * maze->cols].left_wall;
        case 1: return maze->units[current[0] + current[1] * maze->cols].right_wall;
        case 2: return maze->units[current[0] + current[1] * maze->cols].top_wall;
        case 3: return maze->units[current[0] + current[1] * maze->cols].bottom_wall;
        default: return true;
    }
}
bool find_next(uint16_t current[2], uint16_t next[2], maze_t *maze) {
    // sort direction
    int left[3] = {-1, 0, current[0] - maze->end_x};
    int right[3] = {1, 0, maze->end_x - current[0]};
    int up[3] = {0, -1, current[1] - maze->end_y};
    int down[3] = {0, 1, maze->end_y - current[1]};
    int *neighbors[4] = {left, right, up, down};
    qsort(neighbors, 4, sizeof(neighbors[0]), compare_direction_desc);
    printf("%d %d %d %d\n", neighbors[0][2], neighbors[1][2], neighbors[2][2], neighbors[3][2]);
    for (int i = 0; i < 4; ++i) {
        next[0] = current[0] + neighbors[i][0];
        next[1] = current[1] + neighbors[i][1];
        printf("next: %d, %d\n", next[0], next[1]);
        if (next[0] >= 0 &&
            next[0] < maze->cols &&
            next[1] >= 0 &&
            next[1] < maze->rows &&
            !encounter_wall(neighbors[i][0], neighbors[i][1], current, maze) &&
            !maze->units[next[0] + next[1] * maze->cols].visited
        ) {
            return true;
        }
    }
    return false;
}

void goto_next(uint16_t next[2], maze_t *maze) {
    maze->units[next[1] * maze->cols + next[0]].visited = true;
}
