#pragma once
#include <cstdint>

extern "C" __declspec(dllimport) void MConcat(uint8_t * ret, uint8_t *str1, int32_t len1, uint8_t *str2, int32_t len2);
extern "C" __declspec(dllimport) void MReplace(char16_t *ret, int32_t outLen, char16_t *str, int32_t len, char16_t *oldStr, int32_t oldLen, char16_t *newStr, int32_t newLen, int64_t *matches, int32_t matchNumbers);
extern "C" __declspec(dllimport) void MContains(uint8_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void MIndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void MStartIndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, int32_t start, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void MStartCountIndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, int32_t start, int32_t count, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void MStartsWith(uint8_t *ret, char16_t *str, int32_t len, char16_t *valStr, int32_t valLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void MEndsWith(uint8_t *ret, char16_t *str, int32_t len, char16_t *valStr, int32_t valLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void MCompare(int32_t *ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);
extern "C" __declspec(dllimport) void MReverse(char16_t *ret, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void MTrim(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void MTrimStr(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len, char16_t *trimStr, int32_t trimLen);
extern "C" __declspec(dllimport) void MTrimStart(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void MTrimStartStr(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len, char16_t *trimStr, int32_t trimLen);
extern "C" __declspec(dllimport) void MTrimEnd(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void MTrimEndStr(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len, char16_t *trimStr, int32_t trimLen);
extern "C" __declspec(dllimport) void MToLower(char16_t *ret, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void MToUpper(char16_t *ret, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void MSubstring(char16_t *ret, char16_t *str, int32_t len, int32_t start, int32_t count);
extern "C" __declspec(dllimport) void MEquals(uint8_t *ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);
extern "C" __declspec(dllimport) int8_t MTryEncodingConvert(uint8_t *ret, int64_t *retLen, uint8_t *str, int32_t len, int32_t encoding1, int32_t encoding2);