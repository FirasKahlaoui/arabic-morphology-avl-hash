#include <iostream>
#include "UnicodeHelper.h"

int main()
{
    std::cout << "Arabic Morphology System Initialized" << std::endl;

    std::string test = "كتب";
    std::u32string u32test = utf8_to_utf32(test);

    std::cout << "UTF-8 String: " << test << std::endl;
    std::cout << "Length in bytes: " << test.length() << std::endl;          // Should be 6 for 3 chars
    std::cout << "Length in code points: " << u32test.length() << std::endl; // Should be 3

    if (is_arabic(u32test))
    {
        std::cout << "Detected Arabic text." << std::endl;
    }

    return 0;
}
