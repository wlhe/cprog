/**
 * @file unorderedmap.cpp
 * @author wlhe
 * @brief 
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>
#include <unordered_map>


#include "log.h"

int main()
{
    std::unordered_map<std::string, int> m;
    for (int i = 0; i < 1000; i++) {
        m.insert({std::to_string(i), i});

        LOGI("size: %d, %d, %d", static_cast<int>(m.size()), static_cast<int>(sizeof(m)), static_cast<int>(m.max_size()));
    }
    return 0;
}