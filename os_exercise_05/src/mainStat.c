#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "lib2.h"

int main() {
    int arg1, arg2;
    float arg3, arg4;

    int cmd = 0;
    printf("Enter command:\n");
    printf("1 Derivative(float, float)\n");
    printf("2 PrimeCount(int, int)\n");
    printf("3 exit\n\n");
    while (cmd != 3) {
        if(scanf("%d", &cmd) != 1) {
            printf("SCANF ERROR\n");
            exit(-1);
        }
        switch (cmd) {
            case 1:
                if(scanf("%f %f", &arg3, &arg4) != 2) {
                    printf("SCANF ERROR\n");
                    exit(-1);
                }
                printf("%f\n", Derivative(arg3, arg4));
                break;
            case 2:
                if(scanf("%d %d", &arg1, &arg2) != 2) {
                    printf("SCANF ERROR\n");
                    exit(-1);
                }
                printf("%d\n", PrimeCount(arg1, arg2));
                break;
            case 3:
                {break;}
            default:
                fprintf(stderr, "incorrect input, try again\n");
        }
    }
    return 0;
}