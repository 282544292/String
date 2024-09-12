#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, startswith)
{
    String str = String("HELLO WORLD");
    String start_str = String(u"HELLO");
    bool ret = StringMethods::startswith(str, start_str);
    EXPECT_TRUE(ret);

    String start_str2 = String(u"hello");
    bool ret2 = StringMethods::startswith(str, start_str2, true);
    EXPECT_TRUE(ret2);
}