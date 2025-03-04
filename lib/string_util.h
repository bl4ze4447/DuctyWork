//
// Created by Antonie Gabriel Belu on 04.03.2025.
//

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](unsigned char ch) { return !std::isspace(ch); }));
}

// Trim from end (right)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}



#endif //STRING_UTIL_H
