#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, trim)
{
    char16_t str1[] = u"   HELLO WORLD   ";
    String ret = StringMethods::trim(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String("HELLO WORLD"));

    char16_t str2[] = u"000212342000";
    String ret2 = StringMethods::trim(String(str2), String("0"));
    print(ret2);
    EXPECT_TRUE(ret2 == String("212342"));

    String ret3 = StringMethods::trim(String(str2), u'0');
    print(ret3);
    EXPECT_TRUE(ret3 == String("212342"));
}