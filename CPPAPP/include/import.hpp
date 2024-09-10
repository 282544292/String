#include <cstdint>

extern "C" __declspec(dllimport) void Concat(char16_t * ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);
extern "C" __declspec(dllimport) void ReplaceOutLen(int32_t *outLen, char16_t *str, int32_t len, char16_t oldChar, int32_t oldLen, int32_t newLen);
extern "C" __declspec(dllimport) void Replace(char16_t *ret, int32_t outLen, char16_t *str, int32_t len, char16_t *oldStr, int32_t oldLen, char16_t *newStr, int32_t newLen);
extern "C" __declspec(dllimport) void Contains(uint8_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void IndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen);