#include <future>
#include <chrono>

#include <log.h>

int main()
{
    auto f = std::async(std::launch::async, [](){
        using namespace std::chrono;
        std::this_thread::sleep_for(1s);
        return 100;});
    auto r = f.get();

    LOGD("r: %d", r);
    LOGI("r: %d", r);
    LOGW("r: %d", r);
    LOGE("r: %d", r);
    LOGF("r: %d", r);
    return 0;
}