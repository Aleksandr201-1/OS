#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>

const int FILE_LENGHT = 20;
const int STR_LENGHT = 100;

//родительский процесс
void parent (char* data, int fd) {
    char *errorMess = "ERROR";
    while (1) {
        char str[100] = {'\0'};
        scanf("%s", str);
        int size = strlen(str);
        data[0] = size;
        data[1] = -1;
        memcpy(data + 2, str, size + 1);
        if (size == 0) {
            data[2] = '\n';
            break;
        }
        dup2(fd, 1);
        while (data[1] != 1 && data[1] != 0) {}
        if (data[1] == 0) {
            printf("%s\n", errorMess);
        } else {
            printf("%s\n", str);
        }
    }
    wait(NULL);
    close(fd);
}

//дочерний процесс
void child (char* data) {
    while (1) {
        while (data[2] == '\0'){}
        bool result;
        char* str = data + 2;
        int size = data[0];
        if (size == 0) {
            break;
        }
        if(str[0] < 'A' || str[0] > 'Z'){
            data[1] = 0;
        } else {
            data[1] = 1;
        }
        data[2] = '\0';
    }
}

int main () {
    char memfile[FILE_LENGHT];
    char file[FILE_LENGHT];
    printf("Enter name of memory file\n");
    scanf("%s", memfile);
    printf("Enter name of out file\n");
    scanf("%s", file);

    int out_fd = open(file, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
    if (out_fd == -1) {
        fprintf(stderr, "Can't open file\n");
        return -1;
    }
    int mem_fd = open(memfile, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
    if (mem_fd == -1) {
        fprintf(stderr, "Can't open file\n");
        return -1;
    }
    int pid;

    if (ftruncate(mem_fd, STR_LENGHT)) {
        perror("ftruncate");
        return -1;
    }

    char* dataPtr = (char*) mmap(NULL, STR_LENGHT + 3, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0); //Создаем отображение файла в память
    dataPtr[2] = '\0';
    close(mem_fd);
    if (dataPtr == MAP_FAILED) {
        perror("Map");
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        perror("FORK");
    } else if (pid == 0) {
        child(dataPtr);
    } else {
        parent(dataPtr, out_fd);
    }

    munmap(dataPtr, STR_LENGHT);
    close(out_fd);
    return 0;
}
