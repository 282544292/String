#include "../include/string.hpp"
#include <gtest/gtest.h>

TEST(string, compare)
{
    String str1 = String(u"HELLO WORLD");
    String str2 = String(u"HELLO WORLD");
    int ret = StringAPI::compare(str1, str2);
    EXPECT_EQ(ret, 0);

    String str3 = String(u"HELLO WORLD");
    String str4 = String(u"HELLO WORLD!");
    int ret2 = StringAPI::compare(str3, str4);
    EXPECT_EQ(ret2, -1);
}