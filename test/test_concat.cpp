#include "../include/string.hpp"
#include <cstdio>
#include <gtest/gtest.h>

TEST(string, concat)
{
    char16_t str1[] = u"HELLO WORLD";
    char16_t str2[] = u"!";
    String ret = StringAPI::concat(String(str1), String(str2));
    print(ret);
    EXPECT_TRUE(ret == String(u"HELLO WORLD!"));

    char16_t str3[] = u"你好, ";
    char16_t str4[] = u"世界!";
    String ret2 = StringAPI::concat(String(str3), String(str4));
    print(ret2);
    EXPECT_TRUE(ret2 == String(u"你好, 世界!"));

    char32_t str5[] = U"你好，";
    char16_t str6[] = u"世界!";
    String ret3 = StringAPI::concat(String(str5, 3, Encoding::UTF32LE), String(str6));
    print(ret3);
    EXPECT_TRUE(ret3 == String(u"你好，世界!"));
}
