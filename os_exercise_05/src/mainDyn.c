#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <dlfcn.h>

int main() {
    float arg1, arg2;
    int arg3, arg4;
    void* handle = NULL;
    float (*Derivative)(float,float);
    int (*PrimeCount)(int, int);
    handle = dlopen("./lib2D.so", RTLD_LAZY);
    if (handle == NULL) {
        printf("OPEN LIBRARY ERROR\n");
        exit(-1);
    }
    Derivative = dlsym(handle, "Derivative");
    PrimeCount = dlsym(handle, "PrimeCount");
    int cmd = 0, libNum = 0;
    printf("Enter command:\n");
    printf("0 change implementation\n");
    printf("1 Derivative(float, float)\n");
    printf("2 PrimeCount(int, int)\n");
    printf("3 exit\n\n");
    while (cmd != 3) {
        if(scanf("%d", &cmd) != 1) {
            printf("SCANF ERROR\n");
            exit(-1);
        }
        switch (cmd) {
            case 0:
                dlclose(handle);
                if (libNum == 0) {
                    if ((handle = dlopen("./lib1D.so", RTLD_LAZY)) == 0) {
                        printf("OPEN LIBRARY ERROR\n");
                        exit(-1);
                    }
                    libNum = 1;
                } else {
                    if ((handle = dlopen("./lib2D.so", RTLD_LAZY)) == 0) {
                        printf("OPEN LIBRARY ERROR\n");
                        exit(-1);
                    }
                    libNum = 0;
                }
                Derivative = dlsym(handle, "Derivative");
                PrimeCount = dlsym(handle, "PrimeCount");
                break;
            case 1:
                if(scanf("%f %f", &arg1, &arg2) != 2) {
                    printf("SCANF ERROR\n");
                    exit(-1);
                }
                printf("%f\n", (*Derivative)(arg1, arg2));
                break;
            case 2:
                if(scanf("%d %d", &arg3, &arg4) != 2) {
                    printf("SCANF ERROR\n");
                    exit(-1);
                }
                printf("%d\n", (*PrimeCount)(arg3, arg4));
                break;
            case 3:
                {break;}
            default:
                fprintf(stderr, "incorrect input, try again\n");
        }
    }
    dlclose(handle);
    return 0;
}