#include "stack.h"
#include <stdlib.h>

int stack_init(bstack_t* stack, int len) {
    stack->len = len;
    stack->data = malloc(len * sizeof(void *));
    stack->top = -1;
    return 0;
}

int stack_push(bstack_t *stack, void *data) {
    if (stack->top < -1 || stack->top >= stack->len - 1) return -1;
    ++stack->top;
    stack->data[stack->top] = data;
    return 0;
}

int stack_pop(bstack_t *stack, void **data) {
    if (stack->top < 0 || stack->top >= stack->len) return -1;
    *data = stack->data[stack->top];
    --stack->top;
    return 0;
}

int stack_clear(bstack_t *stack) {
    stack->top = -1;
    return 0;
}

int stack_free(bstack_t *stack) {
    if (stack_clear(stack)) return -1;
    for (int i = stack->len; i > 0; i --) {
        free(stack->data[i - 1]);
    }
    free(stack->data);
    return 0;
}

int stack_peek(bstack_t *stack, void **data) {
    if (stack->top < 0) return -1;
    *data = stack->data[stack->top];
    return 0;
}

bool stack_empty(bstack_t *stack) {
    return stack->top < 0;
}
