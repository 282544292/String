#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, reverse)
{
    char16_t str1[] = u"HELLO WORLD";
    String ret = StringMethods::reverse(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String("DLROW OLLEH"));
}