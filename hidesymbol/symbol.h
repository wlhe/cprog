#include <cstdio>

#include <atomic>


#define HAVE_VISIBILITY 1
#if HAVE_VISIBILITY
#define LIB_EXPORT __attribute__((__visibility__("default")))
#else
#define LIB_EXPORT
#endif

class LIB_EXPORT A {
    public:
    LIB_EXPORT void func7();
    void func8();
    private:
    LIB_EXPORT void func13();
    void func14();
};

 class B {
    public:
    LIB_EXPORT void func9();
    void func10();
    private:
    LIB_EXPORT void func15();
    void func16();
};