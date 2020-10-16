#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

//функция получения строки и её размера
int getStr(char **str){
    int size = 0;
    char a = '\0';
    int strSize = 10;
    (*str) = malloc(sizeof(char) * strSize);
    if((*str) == NULL){
        write(STDERR_FILENO, "MEM ERR\n", sizeof(char) * 8);
        exit(-1);
    }
    while(read(0, &a, sizeof(char)) == 1){
        if(a == '\n'){
            break;
        }
        (*str)[size] = a;
        size++;
        if(size == strSize){
            strSize = strSize * 3 / 2;
            (*str) = realloc((*str), sizeof(char) * strSize);
            if((*str) == NULL){
                write(STDERR_FILENO, "MEM ERR\n", sizeof(char) * 8);
                exit(-1);
            }
        }
    }
    if(size == 0){
        free((*str));
        (*str) = NULL;
        return -1;
    } else {
        (*str) = realloc((*str), sizeof(char) * size);
        if((*str) == NULL){
            write(STDERR_FILENO, "MEM ERR\n", sizeof(char) * 8);
            exit(-1);
        }
    }
    return size;
}

//родительский процесс
void parent(int *pipe1, int *pipe2, int fd){
    close(pipe1[0]);
    close(pipe2[1]);
    char *errorMess = "ERROR\n";
    while(1){
        char *str;
        int size = getStr(&str);
        write(pipe1[1], &size, sizeof(int));
        if(size < 0){
            break;
        }
        if(size == 0){
            continue;
        }
        write(pipe1[1], str, sizeof(char) * size);
        free(str);
        bool result;
        read(pipe2[0], &result, sizeof(bool));
        if(!result){
            write(fd, errorMess, sizeof(char) * 6);
        }
    }
    wait(NULL);
    close(fd);
    close(pipe1[1]);
    close(pipe2[0]);
}

//дочерний процесс
void child(int *pipe1, int *pipe2, int fd){
    close(pipe1[1]);
    close(pipe2[0]);
    while(1){
        int size;
        bool result;
        char *str;
        read(pipe1[0], &size, sizeof(int));
        if(size < 0){
            break;
        }
        str = malloc(sizeof(char) * size);
        read(pipe1[0], str, sizeof(char) * size);
        
        if(str[0] < 'A' || str[0] > 'Z' || size == 0){
            result = false;
            write(pipe2[1], &result, sizeof(bool));
        } else {
            result = true;
            write(pipe2[1], &result, sizeof(bool));
            write(fd, str, sizeof(char) * size);
            write(fd, "\n", sizeof(char));
        }
        free(str);
    }
    close(fd);
    close(pipe1[0]);
    close(pipe2[1]);
}

int main(){
    char *filename = NULL;
    while(!filename){
        getStr(&filename);
    }
    int fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, S_IWUSR | S_IRUSR);
    int fd1[2], fd2[2];
    int pid;
    if(pipe(fd1) == -1){
        perror("pipe1 error");
    }
    if(pipe(fd2) == -1){
        perror("pipe2 error");
    }
    pid = fork();
    if(pid == -1){
        perror("FORK");
    } else if(pid == 0){
        child(fd1, fd2, fd);
    } else {
        parent(fd1, fd2, fd);
    }
    free(filename);
    return 0;
}
