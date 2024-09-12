#pragma once
#include <cstdint>

extern "C" __declspec(dllimport) void Concat(char16_t * ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);
extern "C" __declspec(dllimport) void ReplaceOutLen(int32_t *outLen, char16_t *str, int32_t len, char16_t *oldChar, int32_t oldLen, int32_t newLen);
extern "C" __declspec(dllimport) void Replace(char16_t *ret, int32_t outLen, char16_t *str, int32_t len, char16_t *oldStr, int32_t oldLen, char16_t *newStr, int32_t newLen);
extern "C" __declspec(dllimport) void Contains(uint8_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void IndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void StartIndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, int32_t start, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void StartCountIndexOf(int32_t *ret, char16_t *str, int32_t len, char16_t *subStr, int32_t subLen, int32_t start, int32_t count, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void StartsWith(uint8_t *ret, char16_t *str, int32_t len, char16_t *valStr, int32_t valLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void EndsWith(uint8_t *ret, char16_t *str, int32_t len, char16_t *valStr, int32_t valLen, uint8_t ignoreCase);
extern "C" __declspec(dllimport) void Compare(int32_t *ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);
extern "C" __declspec(dllimport) void Reverse(char16_t *ret, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void Trim(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void TrimStr(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len, char16_t *trimStr, int32_t trimLen);
extern "C" __declspec(dllimport) void TrimStart(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void TrimStartStr(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len, char16_t *trimStr, int32_t trimLen);
extern "C" __declspec(dllimport) void TrimEnd(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void TrimEndStr(char16_t *ret, int32_t *outLen, char16_t *str, int32_t len, char16_t *trimStr, int32_t trimLen);
extern "C" __declspec(dllimport) void ToLower(char16_t *ret, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void ToUpper(char16_t *ret, char16_t *str, int32_t len);
extern "C" __declspec(dllimport) void Substring(char16_t *ret, char16_t *str, int32_t len, int32_t start, int32_t count);
extern "C" __declspec(dllimport) void Equals(uint8_t *ret, char16_t *str1, int32_t len1, char16_t *str2, int32_t len2);