#include "../include/string.hpp"
#include "../include/allocator.hpp"
#include <cstdint>
#include<gtest/gtest.h>
#include <iostream>
#include <locale>

TEST(string, encoding)
{
    char32_t str[] = U"你好, 世界!";
    int64_t len = std::char_traits<char32_t>::length(str);
    auto u32str = String(len, Encoding::UTF32LE);
    memory::memcpy<char32_t>(u32str.get_ptr<char32_t>(), str, 7);
    String ret = StringAPI::convert_to_unicode(u32str);
    print(ret);
    EXPECT_TRUE(ret == String(u"你好, 世界!"));
}