// log_test

#include "log.h"

int main(int argc, char **argv)
{
    LOG("test %s\n", "LOG");
    LOGD("test %s", "LOGD");
    LOGI("test %s", "LOGI");
    LOGW("test %s", "LOGW");
    LOGE("test %s", "LOGE");
    LOGF("test %s", "LOGF");
    return 0;
}
