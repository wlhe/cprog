#include <stdio.h>
#include <dlfcn.h>

int test3(int a);

int main(int argc, char **argv)
{
    const char *path = argv[1];

    test3(1);

    void *handle = dlopen(path, RTLD_NOW|RTLD_LOCAL);
    if (handle == NULL) {
        printf("load so error: %s\n", dlerror());
    }

    int (*f)(int) = NULL;
    f = dlsym(handle, "test1");
    if (f != NULL) {
        f(3);
    } else {
        printf("null pointer\n");
    }

    f = dlsym(handle, "test2");
    if (f != NULL) {
        f(6);
    } else {
        printf("null pointer\n");
    }

    getchar();

    dlclose(handle); 
    return 0;
}
