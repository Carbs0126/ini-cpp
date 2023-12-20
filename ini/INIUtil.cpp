//
// Created by Carbs0126 on 2023/12/19.
//

#include "INIUtil.h"

std::string &INIUtil::trim(std::string &s) {
    if (!s.empty()) {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
    return s;
}