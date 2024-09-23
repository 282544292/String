#include "../include/string.hpp"
#include <gtest/gtest.h>

TEST(string, toupper)
{
    char16_t str1[] = u"hello world!";
    String ret = StringAPI::toupper(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String(u"HELLO WORLD!"));
}