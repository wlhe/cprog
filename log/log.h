// log wrapper

#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

#ifndef __cplusplus
extern "C" {
#endif


#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_PURPLE "\033[35m"
#define COLOR_BLUE "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_END "\033[0m\n"

#define COLOR_HIGHLIGHT "\33[1m"

#ifdef LOGTAG
#define _TAG "[" LOGTAG "]"
#else
#define _TAG
#endif

#define ENABLE_CONSOLE_LOG
#ifdef ENABLE_CONSOLE_LOG
#define LOG(fmt, ...) printf(_TAG fmt, ##__VA_ARGS__)
#else
#define LOG
#endif

#define LOGD(fmt, ...) LOG((COLOR_WHITE fmt COLOR_END), ##__VA_ARGS__)
#define LOGI(fmt, ...) LOG((COLOR_GREEN fmt COLOR_END), ##__VA_ARGS__)
#define LOGW(fmt, ...) LOG((COLOR_YELLOW fmt COLOR_END), ##__VA_ARGS__)
#define LOGE(fmt, ...) LOG((COLOR_RED fmt COLOR_END), ##__VA_ARGS__)
#define LOGF(fmt, ...) LOG((COLOR_HIGHLIGHT COLOR_RED fmt COLOR_END), ##__VA_ARGS__)

#ifndef __cplusplus
}
#endif
#endif // __LOG_H__