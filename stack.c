#include "stack.h"
#include <stdlib.h>

t_stack *init_stack(void) {
    t_stack *stack = (t_stack *)malloc(sizeof(t_stack));
    stack->top = NULL;
    return stack;
}

void push(t_stack *stack, int value) {
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

int pop(t_stack *stack) {
    if (stack->top == NULL) return -1; // Stack underflow
    t_node *temp = stack->top;
    int value = temp->value;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

// ...swap, rotate, reverse_rotateの実装...
