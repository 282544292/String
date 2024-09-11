#include <cstdint>
#include <cstring>
#include <iostream>
#include "../include/allocator.hpp"
#include "../include/string.hpp"
#include "../include/errors.hpp"

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

String::String(const char16_t *str, int64_t length) : _length(length)
{
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

String::String(const String &str) : _length(str._length), _is_sso(str._is_sso)
{
    if (_is_sso)
    {
        std::memcpy(_sso_data, str._sso_data, _length + 1);
    }
    else
    {
        _heap_data = memory::zalloc<char16_t>(_length + 1);
        std::memcpy(_heap_data, str._heap_data, _length + 1);
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

String String::set_value(const char16_t value, int64_t index)
{
    if (index < 0)
    {
        throw stringErrors::index_out_of_bounds(index, 0, INT64_MAX);
    }
    if (_is_sso && index <= _SSO_BUFFER_SIZE)
    {
        auto str = String(std::max(_length, index + 1));
        memcpy(str.c_str(), _sso_data, _length);
        str._sso_data[index] = value;
        return str;
    }
    else if (!_is_sso && index < _length)
    {
        auto str = String(_length);
        memcpy(str.c_str(), _heap_data, _length);
        str._heap_data[index] = value;
        return str;
    }
    else
    {
        auto str = String(index + 1);
        memcpy(str.c_str(), c_str(), _length);
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

void print(const String str)
{
    std::wcout << reinterpret_cast<wchar_t *>(str.c_str()) << std::endl;
}