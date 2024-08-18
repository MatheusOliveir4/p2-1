#include <stdio.h>

void printOneToHundredNumbers() {
    for (int i = 1; i <= 100; i++) {
        printf("%d, ",  i);
    }
}

void sumOfOddNumbersFromTenToHundred() {
    int sum = 0;

    for (int i = 10; i <= 100; i++) {
        if (i % 2 != 0) {
            sum += i;
        }
    }

    printf("Soma dos números ímpares de 1 à 100: %d", sum);
}

void printThreeMultipleNumbersWithoutEndingWith3() {
    for (int i = 1; i <= 200; i++) {

        if (i % 3 == 0 && i % 10 != 3) {
            printf("%d, ", i);
        }
    }
}

int main() {
    printf("Números de 1 à 100:\n");
    printOneToHundredNumbers();

    printf("\n\n");
    sumOfOddNumbersFromTenToHundred();

    printf("\n\nMultiplos de 3 sem terminar com 3:\n");
    printThreeMultipleNumbersWithoutEndingWith3();

    printf("\n\n\n");

    return 0;
}