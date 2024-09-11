#pragma once
#include <cstdint>
class String
{
public:
    String(); // 默认构造函数
    String(int64_t length); // 构造空字符串
    String(const char *str); // 从 C 字符串构造
    String(const char16_t *str, int64_t length); // 从 char16_t 数组构造
    String(const String &str); // 拷贝构造函数
    ~String(); // 析构函数

    String set_value(const char16_t value, int64_t index);
    char16_t get_value(int64_t index) const;
    char16_t *c_str() const;

    int64_t strlen() const;
    bool is_sso() const;

private:
    static const int64_t _SSO_BUFFER_SIZE = 48;
    union
    {
        char16_t *_heap_data;
        char16_t _sso_data[_SSO_BUFFER_SIZE + 1];
    };
    int64_t _length;
    bool _is_sso;
};

void print(const String str);