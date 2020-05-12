#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAXLINE 12

int main(void) {
    char line[MAXLINE];
    FILE *fpin;

    fpin = popen("./lower", "r");
    for (;;) {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL) {
            break;
        }
        if (fputs(line, stdout) == EOF) {
            exit(1);
        }
    }
    pclose(fpin);
    putchar('\n');
    exit(0);
}
