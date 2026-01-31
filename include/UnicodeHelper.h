#ifndef UNICODE_HELPER_H
#define UNICODE_HELPER_H

#include <string>
#include <vector>

std::u32string utf8_to_utf32(const std::string &utf8_str);
std::string utf32_to_utf8(const std::u32string &utf32_str);
bool is_arabic(const std::u32string &str);

#endif
