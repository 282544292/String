#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, startswith)
{
    String str = String(u"HELLO WORLD");
    String start_str = String(u"HELLO");
    bool ret = StringAPI::startswith(str, start_str);
    EXPECT_TRUE(ret);

    String start_str2 = String(u"hello");
    bool ret2 = StringAPI::startswith(str, start_str2, true);
    EXPECT_TRUE(ret2);
}