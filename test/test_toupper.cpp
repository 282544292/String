#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, toupper)
{
    char16_t str1[] = u"hello world!";
    String ret = StringMethods::toupper(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String("HELLO WORLD!"));
}