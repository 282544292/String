#include "../include/string.hpp"
#include<gtest/gtest.h>

TEST(string, indexof)
{
    String str = String(u"HELLO WORLD");
    String sub_str = String(u"WORLD");
    int ret = StringAPI::indexof(str, sub_str);
    EXPECT_EQ(ret, 6);

    String sub_str2 = String(u"HeLLo");
    int ret2 = StringAPI::indexof(str, sub_str2, true);
    EXPECT_EQ(ret2, 0);

    String sub_str3 = String(u"ld");
    int ret3 = StringAPI::indexof(str, sub_str3, 3, true);
    EXPECT_EQ(ret3, 9);

    int ret4 = StringAPI::indexof(str, sub_str3, 3, 5, true);
    EXPECT_EQ(ret4, -1);
}