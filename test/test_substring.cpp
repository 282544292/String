#include "../include/string.hpp"
#include <gtest/gtest.h>
TEST(string, substring)
{
    char16_t str1[] = u"HELLO WORLD";
    String ret = StringAPI::substring(String(str1), 0, 5);
    print(ret);
    EXPECT_TRUE(ret == String(u"HELLO"));
}
