#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_LINE 15

static void sig_pipe_handler(int signo) {
    exit(1);
    printf("SIGPIPE caught\n");
};

int main(void) {
    int n, fd1[2], fd2[2];
    pid_t pid;
    char line[MAX_LINE];

    signal(SIGPIPE, sig_pipe_handler);

    pipe(fd1);
    pipe(fd2);

    pid = fork();

    if (pid < 0) {
        exit(1);
    }

    if (pid > 0) {
        close(fd1[0]);
        close(fd2[1]);

        while (fgets(line, MAX_LINE, stdin) != NULL) {
            n = strlen(line);
            write(fd1[1], line, n);
            n = read(fd2[0], line, MAX_LINE);
            if (n == 0) {
                write(STDOUT_FILENO, "child closed pipe", 17);
                break;
            }
            line[n] = 0;
            fputs(line, stdout);
        }
        exit(0);
    } else {
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO) {
            dup2(fd1[0], STDOUT_FILENO);
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO) {
            dup2(fd2[1], STDOUT_FILENO);
            close(fd2[1]);
        }

        execl("./add2", "add2", (char*)0);
    }

    exit(0);
}