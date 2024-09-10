#pragma once
#include <cstdint>
#include "allocator.hpp"
struct String
{
    char16_t *str;
    int64_t length;
};

// 创建字符串
String create_string(int64_t length);
// 设置字符串的值
String set_value(String str, const char16_t value, int64_t index);
// 获取字符串的值
char16_t get_value(const String str, int64_t index);
// 在终端输出字符串
void print(const String str);