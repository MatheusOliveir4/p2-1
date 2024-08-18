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

    printf("Soma: %d", sum);
}

void printThreeMultipleNumbersWithoutEndingWith3() {

    for (int i = 1; i <= 200; i++) {
        if (i % 3 == 0) {
            printf("%d, ", i);
        }
    }
}

int main() {
    printOneToHundredNumbers();

    printf("\n\n\n");

    sumOfOddNumbersFromTenToHundred();

    printf("\n\n\n");

    printThreeMultipleNumbersWithoutEndingWith3();

    printf("\n\n\n");

    return 0;
}