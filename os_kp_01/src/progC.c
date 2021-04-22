#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "term.h"
#include "zmq.h"

int main () {
    signal(SIGINT, termination);
	signal(SIGSEGV, termination);
    printf("starting C...\n");
    bool gotMess = true;
    pid_t myPid = getpid();

    void* contextA = zmq_ctx_new();
	void* respondA = zmq_socket(contextA, ZMQ_PAIR);
    zmq_bind(respondA, "ipc://connectAC");

    void* contextB = zmq_ctx_new();
    void* requestB = zmq_socket(contextB, ZMQ_PAIR);
    zmq_connect(requestB, "ipc://connectCB");

    zmq_send(respondA, &myPid, sizeof(pid_t), 0);
    zmq_recv(respondA, &pid[0], sizeof(pid_t), 0);

    zmq_send(requestB, &myPid, sizeof(pid_t), 0);
    zmq_recv(requestB, &pid[1], sizeof(pid_t), 0);

    while (gotMess) {
        size_t length;
        char line[80];

        zmq_recv(respondA, line, sizeof(char) * (80), 0);
        printf("got message from A: \"%s\"\n", line);

        length = strlen(line);
        if (length == 0) {
            gotMess = false;
        }
        zmq_send(respondA, &gotMess, sizeof(bool), 0);

        zmq_send(requestB, &length, sizeof(size_t), 0);
    }

    zmq_close(respondA);
    zmq_ctx_destroy(contextA);
    zmq_close(requestB);
    zmq_ctx_destroy(contextB);
    return 0;
}