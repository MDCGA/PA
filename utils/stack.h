#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
typedef struct {
    void **data;
    int top;
    int len;
} bstack_t;

int stack_init (bstack_t *stack, int len);
int stack_push (bstack_t *stack, void *data);
int stack_pop (bstack_t *stack, void **data);
int stack_clear (bstack_t *stack);
int stack_free (bstack_t *stack);
int stack_peek(bstack_t *stack, void **data);
/*
 * @brief Check if the stack is empty.
 * @return If the stack is empty return true, else return false.
 */
bool stack_empty (bstack_t *stack);
#endif
