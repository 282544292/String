#include "../include/string.hpp"
#include <gtest/gtest.h>

TEST(string, contains)
{
    char16_t str1[] = u"HELLO WORLD";
    String str = String(u"HELLO WORLD");
    String sub_str = String(u"WORLD");
    bool ret = StringAPI::contains(str, sub_str);
    EXPECT_TRUE(ret);

    String sub_str2 = String(u"HeLLo");
    bool ret2 = StringAPI::contains(str, sub_str2, true);
    EXPECT_TRUE(ret2);
}