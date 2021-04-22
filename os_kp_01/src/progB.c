#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "term.h"
#include "zmq.h"

int main () {
    signal(SIGINT, termination);
	signal(SIGSEGV, termination);
    printf("starting B...\n");
    bool gotMess = true;
    pid_t myPid = getpid();

    void* contextA = zmq_ctx_new();
    void* respondA = zmq_socket(contextA, ZMQ_PAIR);
    zmq_bind(respondA, "ipc://connectAB");

    void* contextC = zmq_ctx_new();
    void* respondC = zmq_socket(contextC, ZMQ_PAIR);
    zmq_bind(respondC, "ipc://connectCB");

    zmq_send(respondA, &myPid, sizeof(pid_t), 0);
    zmq_recv(respondA, &pid[0], sizeof(pid_t), 0);

    zmq_recv(respondC, &pid[1], sizeof(pid_t), 0);
    zmq_send(respondC, &myPid, sizeof(pid_t), 0);

    while (gotMess) {
        size_t length1;
        size_t length2;

        zmq_recv(respondA, &length1, sizeof(size_t), 0);
        zmq_recv(respondC, &length2, sizeof(size_t), 0);

        printf("send by A: %ld\nreceived by C: %ld\n", length1, length2);

        if (length1 == 0) {
            gotMess = false;
        }
    }

    zmq_close(respondA);
	zmq_ctx_destroy(contextA);
    zmq_close(respondC);
	zmq_ctx_destroy(contextC);
    return 0;
}