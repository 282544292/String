#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, endswith)
{
    String str = String(u"HELLO WORLD");
    String end_str = String(u"WORLD");
    bool ret = StringAPI::endswith(str, end_str);
    EXPECT_TRUE(ret);

    String end_str2 = String(u"world");
    bool ret2 = StringAPI::endswith(str, end_str2, true);
    EXPECT_TRUE(ret2);
}