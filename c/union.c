#include <stdio.h>

// typedef union abc
// {
//     char a;
//     int c;
// } abc;


union abc2
{
    short s[5];
    union {
        float y;
        long z;
    }u;
};

int
main()
{
    // abc u;
    // u.a = 'A';
    // printf("size %ld\n", sizeof(u));

    // printf("char %c\n", u.a);
    // printf("chat as int %d\n", u.a);
    // u.c = 66;
    // printf("char %c\n", u.a);
    // printf("char as int %c\n", u.a);
    // printf("char as hex %p\n", (void *)u.a);

    printf("size short %ld\n", sizeof(short));
    printf("size float %ld\n", sizeof(float));
    printf("size long %ld\n", sizeof(long));
    union abc2 a;
    printf("size u2 %ld\n", sizeof(union abc2));
    printf("size u2 %ld\n", sizeof(a.s));
    printf("size u2 %ld\n", sizeof(a.u));
    
}
