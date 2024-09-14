#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, reverse)
{
    char16_t str1[] = u"HELLO WORLD";
    String ret = StringAPI::reverse(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String(u"DLROW OLLEH"));
}