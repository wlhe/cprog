#include <stdio.h>

static int test1(int a)
{
    printf("test 1 input %d\n", a);
    return a;
}


int test3(int a);

__attribute__((visibility("default"))) int test2(int a)
{
    printf("test 2 input %d\n", a);
    test3(10);
    return a;
}
