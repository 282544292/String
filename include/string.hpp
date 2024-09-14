#pragma once
#include <cstdint>
#include <vector>

enum class Side : int64_t
{
    LEFT,
    RIGHT,
    BOTH
};

// 这里的数字是 codepage 对应的数值，方便在 C# 中编码转换使用
enum class Encoding : int32_t
{
    UTF16_LE = 1200,
    UTF16_BE = 1201,
    UTF32LE = 12000,
    UTF32BE = 12001,
    US_ASCII = 20127,
    ISO_8859_1 = 28591,
    UTF8 = 65001,
};


class String
{
public:
    // 构造函数和析构函数区
    String(); // 默认构造函数
    // 按照所给编码分配内存，如果是变长编码，那么 length 为字符数，如果是定长编码，那么 length 字符数组长度
    String(int64_t length, Encoding encoding = Encoding::UTF16_LE);
    String(const char16_t *str); // 从 char16_t 数组构造
    String(const String &str); // 拷贝构造函数
    String(void *str, int64_t length, Encoding encoding); // 从字节数组构造指定编码字符串
    ~String(); // 析构函数
    static String create_utf16_str_from_bytes(void *str, int64_t bytes, Encoding encoding); // 从字节数组构造 utf16 字符串
    static String create_shared_from_string(const String &str); // 从字符串构造共享内存的字符串
    // String slice(int64_t start_index, int64_t length);

    // set_value 的 index 如果超过数组大小, 那么会自动创建更大的数组，并将原数组复制到新数组中再进行操作
    // set_value 和 get_value 目前只支持 UTF16_LE 编码
    String set_value(const char16_t value, int64_t index);
    char16_t get_value(int64_t index) const;
    template<typename T>
    T *get_ptr() const
    {
        return reinterpret_cast<T *>(_data);
        // return reinterpret_cast<T *>(_data) + _offset;
    }

    // 重载运算符
    bool operator==(const String &str) const;
    bool operator!=(const String &str) const;

    // 相当于是截断字符串，该操作不会返回新的字符串，而是直接修改原字符串
    void set_length(int64_t length);

    int64_t strlen() const;
    uint8_t get_size() const;
    // uint8_t get_reused() const;
    Encoding get_encoding() const;

private:
    // 设置字符串的值, 原地修改, 只支持 UTF16_LE 编码
    void _set_value(const char16_t value, int64_t index);
    void *_data;
    int64_t _length;
    Encoding _encoding;
    uint8_t _size;
    // bool _is_fixed_length = true; // 是否是定长编码, [TODO] 目前只支持定长编码
    // uint8_t _reused = 0; // 是否是共享内存
    // int64_t _offset = 0; // 偏移量
};

uint8_t size(Encoding encoding);

// 打印字符串
void print(const String &str);

// String 常用函数
namespace StringAPI
{
std::vector<int64_t> match(const String &str, const String &pattern, bool ignoreCase = false);
String concat(const String &str1, const String &str2);
String replace(const String &str, const String &old_tr, const String &new_str);
bool contains(const String &str, const String &sub_str, bool ignoreCase = false);
// 查找第一个子字符串，返回子字符串的索引，如果没有找到则返回 -1
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
int8_t try_encoding_convert(const String &from, String &to, int64_t out_bytes);
String convert_to_unicode(const String &from);
}
