#include <stdexcept>
#include <iostream>
#include "../include/string.hpp"
#include "../include/errors.hpp"

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
        throw stringErrors::index_out_of_bounds(index, str.length);
    }

    str.str[index] = value;
    return str;
}

char16_t get_value(const String str, int64_t index)
{
    if (index < 0 || index >= str.length)
    {
        throw stringErrors::index_out_of_bounds(index, str.length);
    }

    return str.str[index];
}

void print(const String str)
{
    std::wcout << reinterpret_cast<wchar_t *>(str.str) << std::endl;
}