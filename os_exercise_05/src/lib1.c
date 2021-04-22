#include "lib1.h"

float Derivative (float A, float deltaX) {
    printf("Реализация функции Derivative из первой библиотеки\n");
    return (cos(A + deltaX) - cos(A)) / deltaX;
}

int PrimeCount (int A, int B) {
    printf("Реализация функции PrimeCount из первой библиотеки\n");
    int ans = 0;
    if (A == 1) {
        ++A;
    }
    for (int i = A; i <= B; ++i) {
        for (int j = 2; j < i; ++j) {
            if (i % j == 0) {
                --ans;
                break;
            }
        }
        ++ans;
    }
    return ans;
}
