#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int *data = malloc(sizeof(int) * 100);
    
    // Invalid read of size 4
    // printf("data[99] %i\n", data[100]);


    // Invalid free()
    // free(&data[50]);
}