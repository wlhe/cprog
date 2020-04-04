#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{

    int (*f)(int) = NULL;
    void *handle = dlopen("/home/wlhe/work/cprog/dlsym/libtest.so", RTLD_NOW);
    if (handle == NULL) {
        printf("load so error: %s\n", dlerror());
    }
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
    dlclose(handle); 
    return 0;
}
