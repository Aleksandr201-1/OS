#include "lib2.h"

float Derivative (float A, float deltaX) {
    printf("Реализация функции Derivative из второй библиотеки\n");
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}

int PrimeCount (int A, int B) {
    printf("Реализация функции PrimeCount из второй библиотеки\n");
    if (A == 1) {
        ++A;
    }
    bool ERA[B + 1];
    for (int i = 2; i <= B; ++i) {
        ERA[i] = true;
    }
    int ans = 0;
    int P = 2;
    while (P * P <= B) {
        int i = P * P;
        if (ERA[i]) {
            while (i <= B) {
                ERA[i] = false;
                i += P;
            }
        }
        P++;
    }
    for (int i = A; i <= B; ++i) {
        if (ERA[i]) {
            ans++;
        } 
    }
    return ans;
}
