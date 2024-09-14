#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, tolower)
{
    char16_t str1[] = u"HELLO WORLD";
    String ret = StringAPI::tolower(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String(u"hello world"));
}