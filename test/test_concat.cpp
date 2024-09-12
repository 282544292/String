#include "../include/string.hpp"
#include "../include/utest.h"
#include "../include/import.hpp"
#include <iostream>

UTEST_MAIN();

UTEST(string, concat)
{
    char16_t str1[] = u"HELLO WORLD";
    char16_t str2[] = u"!";
    String ret = StringMethods::concat(String(str1, 11), String(str2, 1));
    print(ret);
}
