#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, reverse)
{
    char16_t str1[] = u"HELLO WORLD";
    String ret = StringMethods::reverse(String(str1));
    print(ret);
    EXPECT_TRUE(ret == String("DLROW OLLEH"));
}