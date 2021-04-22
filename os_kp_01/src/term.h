#ifndef TERM_H
#define TERM_H

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

pid_t pid[2];

void termination (int code) {
    kill(pid[0], SIGKILL);
    kill(pid[1], SIGKILL);
	exit(code);
}

#endif