#include <cstdint>
#include <iostream>
#include "../include/allocator.hpp"
#include "../include/string.hpp"
#include "../include/errors.hpp"
#include "../include/imports.hpp"

String::String() : _length(0), _encoding(Encoding::UTF16_LE), _size(2)
{
    _data = memory::zalloc<char16_t>(1);
    char16_t *ptr = get_ptr<char16_t>();
    ptr[0] = u'\0';
}


String::String(int64_t length, Encoding encoding) : _length(length), _encoding(encoding)
{
    switch (size(encoding))
    {
    case 2:
        _size = 2;
        _data = memory::zalloc<char16_t>(length + 1);
        reinterpret_cast<char16_t *>(_data)[length] = u'\0';
        break;
    case 4:
        _size = 4;
        _data = memory::zalloc<char32_t>(length + 1);
        reinterpret_cast<char32_t *>(_data)[length] = U'\0';
        break;
    case 1:
        _size = 1;
        _data = memory::zalloc<uint8_t>(length + 1);
        reinterpret_cast<uint8_t *>(_data)[length] = '\0';
        break;
    default:
        throw stringErrors::unsupported_encoding();
    }
}

String::String(const char16_t *str) : _encoding(Encoding::UTF16_LE), _size(2)
{
    _length = std::char_traits<char16_t>::length(str);
    _data = memory::zalloc<char16_t>(_length + 1);
    memory::memcpy<char16_t>(_data, str, _length);
    reinterpret_cast<char16_t *>(_data)[_length] = u'\0';
}

String::String(const String &str) : _length(str._length), _encoding(str._encoding), _size(str._size)
{
    switch (_size)
    {
    case 2:
        _data = memory::zalloc<char16_t>(_length + 1);
        memory::memcpy<char16_t>(_data, str._data, _length + 1);
        break;
    case 4:
        _data = memory::zalloc<char32_t>(_length + 1);
        memory::memcpy<char32_t>(_data, str._data, _length + 1);
        break;
    case 1:
        _data = memory::zalloc<uint8_t>(_length + 1);
        memory::memcpy<uint8_t>(_data, str._data, _length + 1);
        break;
    }
}

String::String(void *str, int64_t length, Encoding encoding) : _length(length), _encoding(encoding)
{
    auto size1 = size(encoding);
    switch (size1)
    {
    case 2:
        _size = 2;
        _data = memory::zalloc<char16_t>(length + 1);
        reinterpret_cast<char16_t *>(_data)[length] = u'\0';
        break;
    case 4:
        _size = 4;
        _data = memory::zalloc<char32_t>(length + 1);
        reinterpret_cast<char32_t *>(_data)[length] = U'\0';
        break;
    case 1:
        _size = 1;
        _data = memory::zalloc<uint8_t>(length + 1);
        reinterpret_cast<uint8_t *>(_data)[length] = '\0';
        break;
    default:
        throw stringErrors::unsupported_encoding();
    }
    memory::memcpy<uint8_t>(_data, str, size1 * length);
}

String String::create_utf16_str_from_bytes(void *str, int64_t bytes, Encoding encoding)
{
    if (encoding == Encoding::UTF16_LE)
    {
        auto ret = String(bytes / 2);
        memory::memcpy<uint8_t>(ret._data, str, bytes);
        reinterpret_cast<char16_t *>(ret._data)[ret._length] = u'\0';
        return ret;
    }
    else
    {
        auto from = String();
        from._encoding = encoding;
        from._size = size(encoding);
        from._length = bytes / from._size;
        from._data = str; // 这里实际上是一个引用，因为不是最后结果，所以我并不想为 from 分配内存
        // from._reused = 1;
        auto ret = StringAPI::convert_to_unicode(from);
        return ret;
    }
}

String String::create_shared_from_string(const String &str)
{
    String ret;
    ret._data = str._data;
    ret._length = str._length;
    ret._encoding = str._encoding;
    ret._size = str._size;
    return ret;
}

String::~String()
{
    free(_data);
}

int64_t String::strlen() const
{
    return _length;
}

uint8_t String::get_size() const
{
    return _size;
}

// uint8_t String::get_reused() const
// {
//     return _reused;
// }

Encoding String::get_encoding() const
{
    return _encoding;
}

bool String::operator==(const String &str) const
{
    return StringAPI::equals(*this, str);
}

bool String::operator!=(const String &str) const
{
    return !StringAPI::equals(*this, str);
}

void String::_set_value(const char16_t value, int64_t index)
{
#ifdef DEBUG
    if (index < 0 || index >= _length)
    {
        throw stringErrors::index_out_of_bounds(index, 0, _length);
    }
#endif
    char16_t *ptr = get_ptr<char16_t>();
    ptr[index] = value;
}

void String::set_length(int64_t length)
{
    _length = length;
    _set_value(u'\0', _length);
}

String String::set_value(const char16_t value, int64_t index)
{
    if (index < 0)
    {
        throw stringErrors::index_out_of_bounds(index, 0, INT64_MAX);
    }
    if (index >= _length)
    {
        String new_str = String(index + 1);
        memory::memcpy<char16_t>(new_str._data, _data, _length);
        _set_value(value, index);
        return new_str;
    }
    else {
        String new_str = String(*this);
        new_str._set_value(value, index);
        return new_str;
    }
}


char16_t String::get_value(int64_t index) const
{
    if (index < 0 || index >= _length)
    {
        throw stringErrors::index_out_of_bounds(index, 0, _length - 1);
    }

    char16_t *ptr = get_ptr<char16_t>();
    return ptr[index];
}

uint8_t size(Encoding encoding)
{
    switch (encoding)
    {
    case Encoding::UTF16_LE:
    case Encoding::UTF16_BE:
        return 2;
    case Encoding::UTF32LE:
    case Encoding::UTF32BE:
        return 4;
    case Encoding::US_ASCII:
    case Encoding::ISO_8859_1:
    case Encoding::UTF8:
        return 1;
    default:
        throw stringErrors::unsupported_encoding();
    }
}

void print(const String &str)
{
#ifndef LOCAL_ENCODING
#define LOCAL_ENCODING
    // 设置区域设置为用户首选区域设置
    std::locale::global(std::locale(""));

    // 设置 wcout 使用宽字符区域设置
    std::wcout.imbue(std::locale(""));
#endif
    // if (str.get_reused() == 0)
    std::wcout << reinterpret_cast<wchar_t *>(str.get_ptr<char16_t>()) << std::endl;
    // else
    // {
    //     for (int64_t i = 0; i < str.strlen(); i++)
    //     {
    //         std::wcout << str.get_value(i);
    //     }
    // }
}

// String String::slice(int64_t start, int64_t length)
// {
// #ifdef DEBUG
//     if (start < 0 || start >= _length)
//     {
//         throw stringErrors::out_of_bounds(start, 0, str.strlen());
//     }
// #endif
//     _reused = 1;
//     auto ret = String::create_shared_from_string(*this);
//     ret._offset = start * _size;
//     ret._length = length;
//     return ret;
// }

std::vector<int64_t> StringAPI::match(const String &str, const String &pat_str, bool ignoreCase)
{
    std::vector<int64_t> ret;
    String str1 = str;
    String pat_str1 = pat_str;
    if (ignoreCase)
    {
        str1 = tolower(str);
        pat_str1 = tolower(pat_str);
    }
    int64_t index = indexof(str1, pat_str1);
    int64_t pat_len = pat_str1.strlen();
    while (index != -1)
    {
        ret.push_back(index);
        if (index + pat_len >= str1.strlen())
            break;
        index = indexof(str1, pat_str1, index + pat_len);
    }
    return ret;
}

String StringAPI::concat(const String &str1, const String &str2)
{
    if (str1.get_encoding() == str2.get_encoding())
    {
        auto str = String(str1.strlen() + str2.strlen(), str1.get_encoding());
        MConcat(str.get_ptr<uint8_t>(), str1.get_ptr<uint8_t>(), str1.strlen() * str.get_size(), str2.get_ptr<uint8_t>(), str2.strlen() * str2.get_size());
        return str;
    }
    else
    {
        auto str1_unicode = convert_to_unicode(str1);
        auto str2_unicode = convert_to_unicode(str2);
        auto str = String(str1_unicode.strlen() + str2_unicode.strlen(), Encoding::UTF16_LE);
        MConcat(str.get_ptr<uint8_t>(), str1_unicode.get_ptr<uint8_t>(), str1_unicode.strlen() * str.get_size(), str2_unicode.get_ptr<uint8_t>(), str2_unicode.strlen() * str2_unicode.get_size());
        return str;
    }
}

String StringAPI::replace(const String &str, const String &old_tr, const String &new_str)
{
    int32_t match_numbers = match(str, old_tr).size();
    int32_t out_len = str.strlen() + (new_str.strlen() - old_tr.strlen()) * match_numbers;
    auto ret = String(out_len);
    MReplace(ret.get_ptr<char16_t>(), out_len, str.get_ptr<char16_t>(), str.strlen(), old_tr.get_ptr<char16_t>(), old_tr.strlen(), new_str.get_ptr<char16_t>(), new_str.strlen());
    return ret;
}

bool StringAPI::contains(const String &str, const String &subStr, bool ignoreCase)
{
    uint8_t ret = 0;
    MContains(&ret, str.get_ptr<char16_t>(), str.strlen(), subStr.get_ptr<char16_t>(), subStr.strlen(), ignoreCase);
    return ret != 0;
}

int64_t StringAPI::indexof(const String &str, const String &subStr, bool ignoreCase)
{
    int32_t ret = -1;
    MIndexOf(&ret, str.get_ptr<char16_t>(), str.strlen(), subStr.get_ptr<char16_t>(), subStr.strlen(), ignoreCase);
    return ret;
}

int64_t StringAPI::indexof(const String &str, const String &subStr, int64_t start, bool ignoreCase)
{
    if (start < 0 || start >= str.strlen())
    {
        throw stringErrors::out_of_bounds(start, 0, str.strlen() - 1);
    }
    int32_t ret = -1;
    MStartIndexOf(&ret, str.get_ptr<char16_t>(), str.strlen(), subStr.get_ptr<char16_t>(), subStr.strlen(), start, ignoreCase);
    return ret;
}

int64_t StringAPI::indexof(const String &str, const String &subStr, int64_t start, int64_t count, bool ignoreCase)
{
    if (count < 0)
    {
        throw stringErrors::out_of_bounds(count, 0, INT64_MAX);
    }
    if (start < 0 || start >= str.strlen())
    {
        throw stringErrors::out_of_bounds(start, 0, str.strlen() - 1);
    }
    if (start + count > str.strlen())
    {
        throw stringErrors::out_of_bounds(start + count, 0, str.strlen() - 1);
    }
    int32_t ret = -1;
    MStartCountIndexOf(&ret, str.get_ptr<char16_t>(), str.strlen(), subStr.get_ptr<char16_t>(), subStr.strlen(), start, count, ignoreCase);
    return ret;
}

bool StringAPI::startswith(const String &str, const String &valStr, bool ignoreCase)
{
    uint8_t ret = 0;
    MStartsWith(&ret, str.get_ptr<char16_t>(), str.strlen(), valStr.get_ptr<char16_t>(), valStr.strlen(), ignoreCase);
    return ret != 0;
}

bool StringAPI::endswith(const String &str, const String &valStr, bool ignoreCase)
{
    uint8_t ret = 0;
    MEndsWith(&ret, str.get_ptr<char16_t>(), str.strlen(), valStr.get_ptr<char16_t>(), valStr.strlen(), ignoreCase);
    return ret != 0;
}

int64_t StringAPI::compare(const String &str1, const String &str2)
{
    int32_t ret = 0;
    MCompare(&ret, str1.get_ptr<char16_t>(), str1.strlen(), str2.get_ptr<char16_t>(), str2.strlen());
    return ret;
}

String StringAPI::reverse(const String &str)
{
    auto ret = String(str.strlen());
    MReverse(ret.get_ptr<char16_t>(), str.get_ptr<char16_t>(), str.strlen());
    return ret;
}

String StringAPI::trim(const String &str, Side size)
{
    int32_t out_len = 0;
    auto ret = String(str.strlen());
    switch (size)
    {
    case Side::BOTH:
        MTrim(ret.get_ptr<char16_t>(), &out_len, str.get_ptr<char16_t>(), str.strlen());
        break;
    case Side::LEFT:
        MTrimStart(ret.get_ptr<char16_t>(), &out_len, str.get_ptr<char16_t>(), str.strlen());
        break;
    case Side::RIGHT:
        MTrimEnd(ret.get_ptr<char16_t>(), &out_len, str.get_ptr<char16_t>(), str.strlen());
        break;
    }
    ret.set_length(out_len);
    return ret;
}

String StringAPI::trim(const String &str, const String &trim_str, Side size)
{
    int32_t out_len = 0;
    auto ret = String(str.strlen());
    switch (size)
    {
    case Side::BOTH:
        MTrimStr(ret.get_ptr<char16_t>(), &out_len, str.get_ptr<char16_t>(), str.strlen(), trim_str.get_ptr<char16_t>(), trim_str.strlen());
        break;
    case Side::LEFT:
        MTrimStartStr(ret.get_ptr<char16_t>(), &out_len, str.get_ptr<char16_t>(), str.strlen(), trim_str.get_ptr<char16_t>(), trim_str.strlen());
        break;
    case Side::RIGHT:
        MTrimEndStr(ret.get_ptr<char16_t>(), &out_len, str.get_ptr<char16_t>(), str.strlen(), trim_str.get_ptr<char16_t>(), trim_str.strlen());
        break;
    }
    ret.set_length(out_len);
    return ret;
}

String StringAPI::trim(const String &str, const char16_t value, Side size)
{
    char16_t ch[2] = {value, u'\0'};
    String trim_str = String(ch);
    return trim(str, trim_str, size);
}

String StringAPI::tolower(const String &str)
{
    auto ret = String(str.strlen());
    MToLower(ret.get_ptr<char16_t>(), str.get_ptr<char16_t>(), str.strlen());
    return ret;
}

String StringAPI::toupper(const String &str)
{
    auto ret = String(str.strlen());
    MToUpper(ret.get_ptr<char16_t>(), str.get_ptr<char16_t>(), str.strlen());
    return ret;
}

String StringAPI::substring(const String &str, int64_t start, int64_t length)
{
    if (length < 0)
    {
        throw stringErrors::out_of_bounds(length, 0, INT64_MAX);
    }
    if (start < 0 || start >= str.strlen())
    {
        throw stringErrors::out_of_bounds(start, 0, str.strlen());
    }
    if (start + length > str.strlen())
    {
        throw stringErrors::out_of_bounds(start + length, 0, str.strlen());
    }
    auto ret = String(length);
    MSubstring(ret.get_ptr<char16_t>(), str.get_ptr<char16_t>(), str.strlen(), start, length);
    return ret;
}

bool StringAPI::equals(const String &str1, const String &str2)
{
    uint8_t ret = 0;
    MEquals(&ret, str1.get_ptr<char16_t>(), str1.strlen(), str2.get_ptr<char16_t>(), str2.strlen());
    return ret != 0;
}

int8_t StringAPI::try_encoding_convert(const String &from, String &to, int64_t out_bytes)
{
    int8_t ret;
    ret = MTryEncodingConvert(to.get_ptr<uint8_t>(), &out_bytes, from.get_ptr<uint8_t>(), from.strlen() * from.get_size(), static_cast<int32_t>(from.get_encoding()), static_cast<int32_t>(to.get_encoding()));
    if (ret == 1 && out_bytes < to.strlen())
    {
        to.set_length(out_bytes / to.get_size());
    }
    return ret;
}

String StringAPI::convert_to_unicode(const String &from)
{
    auto size_from = from.get_size();
    // 初始分配与 from 相同大小的内存，如果 size 为 1，则分配 2 倍的内存
    int64_t len = from.strlen();
    int64_t out_bytes = size_from == 1 ? len * 2 : len;
    auto ret = String(out_bytes, Encoding::UTF16_LE);
    int8_t res = try_encoding_convert(from, ret, out_bytes);
    switch (res)
    {
    case 1: // 完全成功
        break;
    case 0: // 失败，且是内存分配不足
        ret = String(out_bytes / 2, Encoding::UTF16_LE);
        try_encoding_convert(from, ret, out_bytes);
        break;
    case -1: // 失败，不支持的编码
        throw stringErrors::convert_failed();
        break;
    }
    return ret;
}