#include "UnicodeHelper.h"
#include <codecvt>
#include <locale>

static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

std::u32string utf8_to_utf32(const std::string &utf8_str)
{
    return converter.from_bytes(utf8_str);
}

std::string utf32_to_utf8(const std::u32string &utf32_str)
{
    return converter.to_bytes(utf32_str);
}

bool is_arabic(const std::u32string &str)
{
    for (char32_t c : str)
    {
        if (c >= 0x0600 && c <= 0x06FF)
        {
            return true;
        }
    }
    return false;
}
