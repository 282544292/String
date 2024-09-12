#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, endswith)
{
    String str = String("HELLO WORLD");
    String end_str = String(u"WORLD");
    bool ret = StringMethods::endswith(str, end_str);
    EXPECT_TRUE(ret);

    String end_str2 = String(u"world");
    bool ret2 = StringMethods::endswith(str, end_str2, true);
    EXPECT_TRUE(ret2);
}