#include "../include/string.hpp"
#include <gtest/gtest.h>

TEST(string, equals)
{
    String str = String(u"HELLO WORLD");
    String str2 = String(u"HELLO WORLD");
    EXPECT_TRUE(StringAPI::equals(str, str2));

    String str3 = String(u"HELLO WORLD");
    String str4 = String(u"HELLO WORLD!");
    EXPECT_TRUE(StringAPI::equals(str3, str4) == false);
}