#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void parse_input(t_stack *stack, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        push(stack, atoi(argv[i]));
    }
}

void sort_stack(t_stack *a, t_stack *b) {
    // ソートアルゴリズムの実装
}

int main(int argc, char **argv) {
    t_stack *a = init_stack();
    t_stack *b = init_stack();

    parse_input(a, argc, argv);
    sort_stack(a, b);

    // 操作の出力

    // メモリ解放
    free(a);
    free(b);
    return 0;
}
