#include <iostream>
#include <cstdint>
#include "./include/import.hpp"

// extern "C" __declspec(dllimport) void Concat(char16_t * ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);
int main()
{
    char16_t str1[] = u"HELLO WORLD";
    char16_t str2[] = u"!";
    char16_t ret[12] = {0};
    Concat(ret, str1, 11, str2, 1);
    std::wcout << reinterpret_cast<wchar_t*>(ret) << std::endl;
    return 0;
}
