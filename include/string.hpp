#pragma once
#include <cstdint>
class String
{
public:
    String(); // 默认构造函数
    String(int64_t length); // 构造空字符串
    String(const char *str); // 从 C 字符串构造
    String(const char16_t *str); // 从 char16_t 数组构造
    String(const String &str); // 拷贝构造函数
    ~String(); // 析构函数

    // set_value的 index 如果超过数组大小, 那么会自动创建更大的数组，并将原数组复制到新数组中再进行操作
    String set_value(const char16_t value, int64_t index);
    char16_t get_value(int64_t index) const;
    char16_t *c_str() const;

    // 重载运算符
    bool operator==(const String &str) const;
    bool operator!=(const String &str) const;

    // 相当于是截断字符串，该操作不会返回新的字符串，而是直接修改原字符串
    void set_length(int64_t length);

    int64_t strlen() const;
    bool is_sso() const;

private:
    // 设置字符串的值, 原地修改
    void _set_value(const char16_t value, int64_t index);
    static const int64_t _SSO_BUFFER_SIZE = 15;
    union
    {
        char16_t *_heap_data;
        char16_t _sso_data[_SSO_BUFFER_SIZE + 1];
    };
    int64_t _length;
    bool _is_sso;
};

enum Side : int64_t
{
    LEFT,
    RIGHT,
    BOTH
};

void print(const String &str);

// String 常用函数
namespace StringMethods
{
String concat(const String &str1, const String &str2);
String replace(const String &str, const String &old_tr, const String &new_str);
bool contains(const String &str, const String &sub_str, bool ignoreCase = false);
// 查找子字符串，返回子字符串的索引，如果没有找到则返回 -1
int64_t indexof(const String &str, const String &sub_str, bool ignoreCase = false);
int64_t indexof(const String &str, const String &sub_str, int64_t start, bool ignoreCase = false);
int64_t indexof(const String &str, const String &sub_str, int64_t start, int64_t count, bool ignoreCase = false);
bool startswith(const String &str, const String &val_str, bool ignoreCase = false);
bool endswith(const String &str, const String &val_str, bool ignoreCase = false);
// 比较两个字符串，返回值为 0 表示相等，-1 表示 str1 小于 str2，1 表示 str1 大于 str2
int64_t compare(const String &str1, const String &str2);
String reverse(const String &str);
// 去除字符串两/左/右端的空白字符
String trim(const String &str, Side size = Side::BOTH);
// 去除字符串两/左/右端的指定多个字符
String trim(const String &str, const String &trim_str, Side size = Side::BOTH);
// 去除字符串两/左/右端的指定字符
String trim(const String &str, const char16_t value, Side size = Side::BOTH);
String tolower(const String &str);
String toupper(const String &str);
// 0-based
String substring(const String &str, int64_t start, int64_t legnth);
bool equals(const String &str1, const String &str2);
}