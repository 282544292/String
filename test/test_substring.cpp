#include "../include/string.hpp"
#include "../include/utest.h"
#include "../include/import.hpp"
#include <iostream>
UTEST(string, substring)
{
    char16_t str1[] = u"HELLO WORLD";
    print(String(str1, 11));
    String ret = StringMethods::substring(String(str1, 11), 0, 5);
    print(ret);
}
