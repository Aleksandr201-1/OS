#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "term.h"
#include "zmq.h"

int main () {
    signal(SIGINT, termination);
	signal(SIGSEGV, termination);
    printf("starting A...\n");
    bool gotMess = true;
    pid_t myPid = getpid();

    void* contextC = zmq_ctx_new();
	void* requestC = zmq_socket(contextC, ZMQ_PAIR);
    zmq_connect(requestC, "ipc://connectAC");

    void* contextB = zmq_ctx_new();
    void* requestB = zmq_socket(contextB, ZMQ_PAIR);
    zmq_connect(requestB, "ipc://connectAB");

    zmq_recv(requestC, &pid[0], sizeof(pid_t), 0);
    zmq_send(requestC, &myPid, sizeof(pid_t), 0);

    zmq_recv(requestB, &pid[1], sizeof(pid_t), 0);
    zmq_send(requestB, &myPid, sizeof(pid_t), 0);

    while (gotMess) {
        char line[80] = {'\0'};
        printf("enter line: ");
        fgets(line, 80, stdin);
        size_t length = strlen(line);
        if (length > 0) {
            line[length - 1] = '\0';
            --length;
        }

        printf("sending message to C\n");
        zmq_send(requestC, (void*)line, sizeof(char) * (80), 0);
        zmq_recv(requestC, &gotMess, sizeof(bool), 0);

        zmq_send(requestB, &length, sizeof(size_t), 0);
    }

    zmq_close(requestC);
	zmq_ctx_destroy(contextC);
    zmq_close(requestB);
    zmq_ctx_destroy(contextB);
    return 0;
}