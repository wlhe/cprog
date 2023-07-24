#include <chrono>
#include <future>
#include <thread>

#include "log.h"

using namespace std::chrono;

void test1()
{
    auto f = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(1s);
        return 100;
    });
    auto r = f.get();

    LOGD("r: %d", r);
    LOGI("r: %d", r);
    LOGW("r: %d", r);
    LOGE("r: %d", r);
    LOGF("r: %d", r);
}

int main()
{
    auto id = std::this_thread::get_id();
    LOGI("main id: %p", *reinterpret_cast<void **>(&id));
    auto f = std::async(std::launch::deferred, []() {
        auto id = std::this_thread::get_id();
        LOGI("async id: %p", *reinterpret_cast<void **>(&id));

        LOGD("async: ");
        std::this_thread::sleep_for(6s);
        return 10;
    });

    LOGI("wait call get");
    std::this_thread::sleep_for(1s);
    LOGI("call wait");
    f.wait();
    LOGI("Wait returned");
    LOGI("call get");
    auto r = f.get();
    LOGI("call returned");

    LOGD("r: %d", r);
    LOGI("r: %d", r);
    LOGW("r: %d", r);
    LOGE("r: %d", r);
    LOGF("r: %d", r);

    return 0;
}