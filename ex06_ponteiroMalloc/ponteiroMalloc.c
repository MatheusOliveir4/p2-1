#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *) malloc(sizeof(int));
    
    if (!ptr) {
        printf("Memória não alocada!");
        return 1;
    }
    
    *ptr = 20;
    printf("%p - %d", ptr, *ptr);

    *ptr *= 4;
    printf("\n%p - %d", ptr, *ptr);

    free(ptr);

    return 0;
}