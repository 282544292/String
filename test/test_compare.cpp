#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, compare)
{
    String str1 = String("HELLO WORLD");
    String str2 = String("HELLO WORLD");
    int ret = StringMethods::compare(str1, str2);
    EXPECT_EQ(ret, 0);

    String str3 = String("HELLO WORLD");
    String str4 = String("HELLO WORLD!");
    int ret2 = StringMethods::compare(str3, str4);
    EXPECT_EQ(ret2, -1);
}