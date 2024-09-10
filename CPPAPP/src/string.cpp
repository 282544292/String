#include <stdexcept>
#include <iostream>
#include "../include/string.hpp"

String create_string(int64_t length)
{
    String result;
    result.str = memory::zalloc<char16_t>(length);
    result.length = length;
    return result;
}

String set_value(String str, const char16_t value, int64_t index)
{
    if (index < 0 || index >= str.length)
    {
        // [TODO]
        throw std::runtime_error("index out of bounds");
    }

    str.str[index] = value;
    return str;
}

char16_t get_value(const String str, int64_t index)
{
    if (index < 0 || index >= str.length)
    {
        // [TODO]
        throw std::runtime_error("index out of bounds");
    }

    return str.str[index];
}

void print(const String str)
{
    std::wcout << reinterpret_cast<wchar_t *>(str.str) << std::endl;
}