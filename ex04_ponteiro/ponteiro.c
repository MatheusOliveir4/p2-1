#include <stdio.h>

int main() {
    int min = 10, max = 20;
    int *ptr;
    printf("min = %d - max = %d - ptr = %p\n", min, max, ptr);

    ptr = &min;
    printf("min = %d - max = %d - ptr = %d\n", min, max, *ptr);
    
    return 0;
}