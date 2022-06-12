#include <cstdio>


#include "symbol.h"

extern "C" {
LIB_EXPORT void func1() {
    printf("%s\n", __func__);
}

void func2() {
    printf("%s\n", __func__);
}
}

LIB_EXPORT void func3() {
    printf("%s\n", __func__);
}

void func4() {
    printf("%s\n", __func__);
}

namespace ht {
LIB_EXPORT void func5() {
    printf("%s\n", __func__);
}

void func6() {
    printf("%s\n", __func__);
}
}

void A::func7() {
printf("%s\n", __func__);
}

void A::func8() {
printf("%s\n", __func__);
}

void A::func13() {
printf("%s\n", __func__);
}

void A::func14() {
printf("%s\n", __func__);
}

void B::func9() {
printf("%s\n", __func__);
}

void B::func10() {
printf("%s\n", __func__);
}

void B::func15() {
printf("%s\n", __func__);
}

void B::func16() {
printf("%s\n", __func__);
}

namespace ns LIB_EXPORT {
LIB_EXPORT void func11() {
    printf("%s\n", __func__);
}

void func12() {
    printf("%s\n", __func__);
}
}