#include "../include/string.hpp"
#include "../include/utest.h"

UTEST(string, equals)
{
    String str = String("HELLO WORLD");
    String str2 = String("HELLO WORLD");
    EXPECT_TRUE(StringMethods::equals(str, str2));

    String str3 = String("HELLO WORLD");
    String str4 = String("HELLO WORLD!");
    EXPECT_TRUE(StringMethods::equals(str3, str4) == false);
}