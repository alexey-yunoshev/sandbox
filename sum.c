#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_LINE 15

int main(void) {
    int number_of_chars, int1, int2;
    char line[MAX_LINE];
    while((number_of_chars = read(STDIN_FILENO, line, MAX_LINE)) > 0) {
        line[number_of_chars] = 0;
        if (sscanf(line, "%d%d", &int1, &int2) == 2) {
            sprintf(line, "%d\n", int1 + int2);
            number_of_chars = strlen(line);
            write(STDOUT_FILENO, line, number_of_chars);
        } else {
            write(STDOUT_FILENO, "invalid args\n", 13);
        }
    }
    exit(0);
}