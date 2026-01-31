#ifndef UNICODE_HELPER_H
#define UNICODE_HELPER_H

#include <string>
#include <vector>

// Convert standard UTF-8 string to UTF-32 (u32string)
std::u32string utf8_to_utf32(const std::string &utf8_str);

// Convert UTF-32 string back to UTF-8
std::string utf32_to_utf8(const std::u32string &utf32_str);

// Helper to check if a string contains valid Arabic characters (basic check)
bool is_arabic(const std::u32string &str);

#endif // UNICODE_HELPER_H
