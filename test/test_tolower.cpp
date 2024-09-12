#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, tolower)
{
    char16_t str1[] = u"HELLO WORLD";
    String ret = StringMethods::tolower(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String("hello world"));
}