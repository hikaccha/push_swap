#include <stdio.h>

typedef struct s_point {
    int x;
    int y;
} t_point;

int main() {
    t_point point = {10, 20};
    t_point *p_ptr = &point;
    
    // アロー演算子を使用してメンバにアクセス
    printf("x: %d, y: %d\n", p_ptr->x, p_ptr->y);
    
    // (*p_ptr).x と同じ意味
    printf("x: %d, y: %d\n", (*p_ptr).x, (*p_ptr).y);
    
    return 0;
}
