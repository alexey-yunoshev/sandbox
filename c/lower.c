#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int c;

    while((c = getchar()) != EOF) {
        if (isupper(c)) {
            c = tolower(c);
        }
        if (putchar(c) == EOF) {
            exit(1);
        }
        if (c == '\n') {
            fflush(stdout);
        }
    }
    exit(0);
}
