#include <stdio.h>

// uncomment to get make them both 6 bytes large
// it is a trade-off between memory and CPU cycles wastage
// eithre way, something will be wasted
// #pragma pack(1)

typedef struct small
{
    char a;
    char b;
    int c;
} small;

typedef struct big
{
    char a;
    int c;
    char b;
} big;


int
main()
{
    printf("small %ld\n", sizeof(small));
    printf("big %ld\n", sizeof(big));

    struct big* s[10];
    printf("small *array %ld\n", sizeof(s));
    struct big sa[10];
    printf("small array %ld\n", sizeof(sa));

    big* b1;
    big b2;
    printf("b1 %ld\n", sizeof(b1));
    printf("b2 %ld\n", sizeof(b2));
    

}
