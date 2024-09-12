#include <cstdint>
#include <cstring>
#include <iostream>
#include "../include/allocator.hpp"
#include "../include/string.hpp"
#include "../include/errors.hpp"
#include "../include/import.hpp"

String::String() : _is_sso(true), _length(0)
{
    _sso_data[0] = u'\0';
}

String::String(int64_t length) : _length(length)
{
    if (_length > _SSO_BUFFER_SIZE)
    {
        _is_sso = false;
        _heap_data = memory::zalloc<char16_t>(_length + 1);
        _heap_data[_length] = u'\0';
    }
    else
    {
        _is_sso = true;
        _sso_data[_length] = u'\0';
    }
}

String::String(const char *str)
{
    _length = std::strlen(str);
    if (_length > _SSO_BUFFER_SIZE)
    {
        _is_sso = false;
        _heap_data = memory::zalloc<char16_t>(_length + 1);
        for (int64_t i = 0; i < _length; i++)
        {
            _heap_data[i] = str[i];
        }
        _heap_data[_length] = u'\0';
    }
    else
    {
        _is_sso = true;
        for (int64_t i = 0; i < _length; i++)
        {
            _sso_data[i] = str[i];
        }
        _sso_data[_length] = u'\0';
    }
}

String::String(const char16_t *str)
{
    _length = std::char_traits<char16_t>::length(str);
    if (_length > _SSO_BUFFER_SIZE)
    {
        _is_sso = false;
        _heap_data = memory::zalloc<char16_t>(_length + 1);
        memory::memcpy<char16_t>(_heap_data, str, _length);
        _heap_data[_length] = u'\0';
    }
    else
    {
        _is_sso = true;
        memory::memcpy<char16_t>(_sso_data, str, _length);
        _sso_data[_length] = u'\0';
    }
}

String::String(const String &str) : _length(str._length)
{
    if (_length <= _SSO_BUFFER_SIZE)
    {
        _is_sso = true;
        memory::memcpy<char16_t>(_sso_data, str.c_str(), _length + 1);
    }
    else
    {
        _is_sso = false;
        _heap_data = memory::zalloc<char16_t>(_length + 1);
        memory::memcpy<char16_t>(_heap_data, str._heap_data, _length + 1);
    }
}

String::~String()
{
    if (!_is_sso)
    {
        free(_heap_data);
    }
}

int64_t String::strlen() const
{
    return _length;
}

bool String::is_sso() const
{
    return _is_sso;
}

char16_t *String::c_str() const
{
    if (_is_sso)
    {
        return const_cast<char16_t *>(_sso_data);
    }
    return _heap_data;
}

bool String::operator==(const String &str) const
{
    return StringMethods::equals(*this, str);
}

bool String::operator!=(const String &str) const
{
    return !StringMethods::equals(*this, str);
}

void String::_set_value(const char16_t value, int64_t index)
{
#ifdef DEBUG
    if (index < 0 || index >= _length)
    {
        throw stringErrors::index_out_of_bounds(index, 0, _length);
    }
#endif
    if (_is_sso)
    {
        _sso_data[index] = value;
    }
    else
    {
        _heap_data[index] = value;
    }
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
    if (_is_sso && index <= _SSO_BUFFER_SIZE)
    {
        auto str = String(std::max(_length, index + 1));
        memory::memcpy<char16_t>(str.c_str(), _sso_data, _length);
        str._sso_data[index] = value;
        return str;
    }
    else if (!_is_sso && index < _length)
    {
        auto str = String(_length);
        memory::memcpy<char16_t>(str.c_str(), _heap_data, _length);
        str._heap_data[index] = value;
        return str;
    }
    else
    {
        auto str = String(index + 1);
        memory::memcpy<char16_t>(str.c_str(), c_str(), _length);
        str._heap_data[index] = value;
        return str;
    }
}


char16_t String::get_value(int64_t index) const
{
    if (index < 0 || index >= _length)
    {
        throw stringErrors::index_out_of_bounds(index, 0, _length);
    }

    if (_is_sso)
    {
        return _sso_data[index];
    }
    else
    {
        return _heap_data[index];
    }
}

void print(const String &str)
{
    std::wcout << reinterpret_cast<wchar_t *>(str.c_str());
    std::cout<<std::endl;
}

String StringMethods::concat(const String &str1, const String &str2)
{
    auto str = String(str1.strlen() + str2.strlen());
    Concat(str.c_str(), str1.c_str(), str1.strlen(), str2.c_str(), str2.strlen());
    return str;
}

String StringMethods::replace(const String &str, const String &old_tr, const String &new_str)
{
    int32_t out_len = 0;
    ReplaceOutLen(&out_len, str.c_str(), str.strlen(), old_tr.c_str(), old_tr.strlen(), new_str.strlen());
    auto ret = String(out_len);
    Replace(ret.c_str(), out_len, str.c_str(), str.strlen(), old_tr.c_str(), old_tr.strlen(), new_str.c_str(), new_str.strlen());
    return ret;
}

bool StringMethods::contains(const String &str, const String &subStr, bool ignoreCase)
{
    uint8_t ret = 0;
    Contains(&ret, str.c_str(), str.strlen(), subStr.c_str(), subStr.strlen(), ignoreCase);
    return ret != 0;
}

int64_t StringMethods::indexof(const String &str, const String &subStr, bool ignoreCase)
{
    int32_t ret = -1;
    IndexOf(&ret, str.c_str(), str.strlen(), subStr.c_str(), subStr.strlen(), ignoreCase);
    return ret;
}

int64_t StringMethods::indexof(const String &str, const String &subStr, int64_t start, bool ignoreCase)
{
    if (start < 0 || start >= str.strlen())
    {
        throw stringErrors::out_of_bounds(start, 0, str.strlen());
    }
    int32_t ret = -1;
    StartIndexOf(&ret, str.c_str(), str.strlen(), subStr.c_str(), subStr.strlen(), start, ignoreCase);
    return ret;
}

int64_t StringMethods::indexof(const String &str, const String &subStr, int64_t start, int64_t count, bool ignoreCase)
{
    if (count < 0)
    {
        throw stringErrors::out_of_bounds(count, 0, INT64_MAX);
    }
    if (start < 0 || start >= str.strlen())
    {
        throw stringErrors::out_of_bounds(start, 0, str.strlen());
    }
    if (start + count > str.strlen())
    {
        throw stringErrors::out_of_bounds(start + count, 0, str.strlen());
    }
    int32_t ret = -1;
    StartCountIndexOf(&ret, str.c_str(), str.strlen(), subStr.c_str(), subStr.strlen(), start, count, ignoreCase);
    return ret;
}

bool StringMethods::startswith(const String &str, const String &valStr, bool ignoreCase)
{
    uint8_t ret = 0;
    StartsWith(&ret, str.c_str(), str.strlen(), valStr.c_str(), valStr.strlen(), ignoreCase);
    return ret != 0;
}

bool StringMethods::endswith(const String &str, const String &valStr, bool ignoreCase)
{
    uint8_t ret = 0;
    EndsWith(&ret, str.c_str(), str.strlen(), valStr.c_str(), valStr.strlen(), ignoreCase);
    return ret != 0;
}

int64_t StringMethods::compare(const String &str1, const String &str2)
{
    int32_t ret = 0;
    Compare(&ret, str1.c_str(), str1.strlen(), str2.c_str(), str2.strlen());
    return ret;
}

String StringMethods::reverse(const String &str)
{
    auto ret = String(str.strlen());
    Reverse(ret.c_str(), str.c_str(), str.strlen());
    return ret;
}

String StringMethods::trim(const String &str, Side size)
{
    int32_t out_len = 0;
    auto ret = String(str.strlen());
    switch (size)
    {
    case Side::BOTH:
        Trim(ret.c_str(), &out_len, str.c_str(), str.strlen());
        break;
    case Side::LEFT:
        TrimStart(ret.c_str(), &out_len, str.c_str(), str.strlen());
        break;
    case Side::RIGHT:
        TrimEnd(ret.c_str(), &out_len, str.c_str(), str.strlen());
        break;
    }
    ret.set_length(out_len);
    return ret;
}

String StringMethods::trim(const String &str, const String &trim_str, Side size)
{
    int32_t out_len = 0;
    auto ret = String(str.strlen());
    switch (size)
    {
    case Side::BOTH:
        TrimStr(ret.c_str(), &out_len, str.c_str(), str.strlen(), trim_str.c_str(), trim_str.strlen());
        break;
    case Side::LEFT:
        TrimStartStr(ret.c_str(), &out_len, str.c_str(), str.strlen(), trim_str.c_str(), trim_str.strlen());
        break;
    case Side::RIGHT:
        TrimEndStr(ret.c_str(), &out_len, str.c_str(), str.strlen(), trim_str.c_str(), trim_str.strlen());
        break;
    }
    ret.set_length(out_len);
    return ret;
}

String StringMethods::trim(const String &str, const char16_t value, Side size)
{
    char16_t ch[2] = {value, u'\0'};
    String trim_str = String(ch);
    return trim(str, trim_str, size);
}

String StringMethods::tolower(const String &str)
{
    auto ret = String(str.strlen());
    ToLower(ret.c_str(), str.c_str(), str.strlen());
    return ret;
}

String StringMethods::toupper(const String &str)
{
    auto ret = String(str.strlen());
    ToUpper(ret.c_str(), str.c_str(), str.strlen());
    return ret;
}

String StringMethods::substring(const String &str, int64_t start, int64_t length)
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
    Substring(ret.c_str(), str.c_str(), str.strlen(), start, length);
    return ret;
}

bool StringMethods::equals(const String &str1, const String &str2)
{
    uint8_t ret = 0;
    Equals(&ret, str1.c_str(), str1.strlen(), str2.c_str(), str2.strlen());
    return ret != 0;
}