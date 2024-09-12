#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, concat)
{
    char16_t str1[] = u"HELLO WORLD";
    char16_t str2[] = u"!";
    String ret = StringMethods::concat(String(str1), String(str2));
    print(ret);
    EXPECT_TRUE(ret == String("HELLO WORLD!"));
}
