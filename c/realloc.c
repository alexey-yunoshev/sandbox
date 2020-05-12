#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str = malloc(17);
    if (str == NULL) {
        printf("Allocation error");
        exit(1);
    }

    strcpy(str, "This is 16 chars");
    str = realloc(str, 18);
    if (str == NULL) {
        printf("Allocation error");
        exit(1);
    }

    strcat(str, ".");
    free(str);
    return 0;
}