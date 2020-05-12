#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

// Will occupy the specified amount of memory in mebibytes
//
// Usage
// ./memory-user [int]
//
// Example
// ./memory-user 100
int main(int argc, char *argv[])
{
    printf("pid %i\n", getpid());
    int elements = atoi(argv[1]) * 256 * 1024;
    int *arr = malloc(elements * sizeof(int));
    printf("%p\n", &arr);
    for (int i = 0; i < elements; i++) {
        arr[i] = i;
    }
    printf("arr %i\n", arr[elements - 1]);
    sleep(999);
    return 0;
}