#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, replace)
{
    char16_t str1[] = u"HELLO WORLD";
    String str = String(str1);
    String old_str = String(u"WORLD");
    String new_str = String(u"WORLD!");
    String ret = StringMethods::replace(String(str1), old_str, new_str);
    print(ret);
    EXPECT_TRUE(ret == String("HELLO WORLD!"));
}