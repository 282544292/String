using System.Runtime.InteropServices;

namespace CSharpStrLib;

public class String
{
    private readonly static ushort[] whiteSpan = { 32, 9, 10, 11, 12, 13 };

    public static void ToLower(Span<ushort> str)
    {

        for (int i = 0; i < str.Length; i++)
        {
            if (str[i] <= char.MaxValue)
            {
                str[i] = (ushort)char.ToLowerInvariant((char)str[i]);
            }
        }
        return;
    }

    public static void ToUpper(Span<ushort> str)
    {
        for (int i = 0; i < str.Length; i++)
        {
            if (str[i] <= char.MaxValue)
            {
                str[i] = (ushort)char.ToUpperInvariant((char)str[i]);
            }
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "ReplaceOutLen")]
    public static unsafe void ReplaceOutLen(int* outLen, ushort* str, int len, ushort* oldChar, int oldLen, int newLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var oldCharSpan = new Span<ushort>(oldChar, oldLen);

        int occurrences = 0;
        int srcIndex = 0;
        int index = strSpan.IndexOf(oldCharSpan);
        while (index != -1)
        {
            occurrences++;
            srcIndex = index + oldCharSpan.Length;
            index = strSpan.Slice(srcIndex).IndexOf(oldCharSpan);
        }

        *outLen = strSpan.Length + occurrences * (newLen - oldLen);
    }

    [UnmanagedCallersOnly(EntryPoint = "Replace")]
    public static unsafe void Replace(ushort* ret, int outLen, ushort* str, int len, ushort* oldChar, int oldLen, ushort* newChar, int newLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var oldCharSpan = new Span<ushort>(oldChar, oldLen);
        var newCharSpan = new Span<ushort>(newChar, newLen);

        int srcIndex = 0;
        int destIndex = 0;
        var resultSpan = new Span<ushort>(ret, outLen);
        int index = strSpan.IndexOf(oldCharSpan);
        while (index != -1)
        {
            strSpan.Slice(srcIndex, index - srcIndex).CopyTo(resultSpan.Slice(destIndex));
            destIndex += index - srcIndex;
            srcIndex = index + oldCharSpan.Length;
            newCharSpan.CopyTo(resultSpan.Slice(destIndex));
            destIndex += newCharSpan.Length;
            index = strSpan.Slice(srcIndex).IndexOf(oldCharSpan);
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "Contains")]
    public static unsafe void Contains(byte* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        int result = -1;
        if (ignoreCase == 1)
        {
            ushort* ptr1 = stackalloc ushort[len];
            var ptr1Span = new Span<ushort>(ptr1, len);
            strSpan.CopyTo(ptr1Span);
            ushort* ptr2 = stackalloc ushort[valueLen];
            var ptr2Span = new Span<ushort>(ptr2, valueLen);
            valueSpan.CopyTo(ptr2Span);
            ToLower(ptr1Span);
            ToLower(ptr2Span);
            result = ptr1Span.IndexOf(ptr2Span);
        }
        else
        {
            result = strSpan.IndexOf(valueSpan);
        }
        if (result == -1)
        {
            *ret = 0;
        }
        else
        {
            *ret = 1;
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "IndexOf")]
    public static unsafe void IndexOf(int* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        if (ignoreCase == 1)
        {
            ushort* ptr1 = stackalloc ushort[len];
            var ptr1Span = new Span<ushort>(ptr1, len);
            strSpan.CopyTo(ptr1Span);
            ushort* ptr2 = stackalloc ushort[valueLen];
            var ptr2Span = new Span<ushort>(ptr2, valueLen);
            valueSpan.CopyTo(ptr2Span);
            ToLower(ptr1Span);
            ToLower(ptr2Span);
            *ret = ptr1Span.IndexOf(ptr2Span);
        }
        else
        {
            *ret = strSpan.IndexOf(valueSpan);
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "StartCountIndexOf")]
    public static unsafe void StartCountIndexOf(int* ret, ushort* str, int len, ushort* value, int valueLen, int start, int count, byte ignoreCase)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        int outIndex = -1;
        if (ignoreCase == 1)
        {
            ushort* ptr1 = stackalloc ushort[len];
            var ptr1Span = new Span<ushort>(ptr1, len);
            strSpan.CopyTo(ptr1Span);
            ushort* ptr2 = stackalloc ushort[valueLen];
            var ptr2Span = new Span<ushort>(ptr2, valueLen);
            valueSpan.CopyTo(ptr2Span);
            ToLower(ptr1Span);
            ToLower(ptr2Span);
            outIndex = ptr1Span.Slice(start, count).IndexOf(ptr2Span);
        }
        else
        {
            outIndex = strSpan.Slice(start, count).IndexOf(valueSpan);
        }
        if (outIndex == -1)
        {
            *ret = -1;
        }
        else
        {
            *ret = outIndex + start;
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "StartIndexOf")]
    public static unsafe void StartIndexOf(int* ret, ushort* str, int len, ushort* value, int valueLen, int start, byte ignoreCase)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        int outIndex = -1;
        if (ignoreCase == 1)
        {
            ushort* ptr1 = stackalloc ushort[len];
            var ptr1Span = new Span<ushort>(ptr1, len);
            strSpan.CopyTo(ptr1Span);
            ushort* ptr2 = stackalloc ushort[valueLen];
            var ptr2Span = new Span<ushort>(ptr2, valueLen);
            valueSpan.CopyTo(ptr2Span);
            ToLower(ptr1Span);
            ToLower(ptr2Span);
            outIndex = ptr1Span.Slice(start).IndexOf(ptr2Span);
        }
        else
        {
            outIndex = strSpan.Slice(start).IndexOf(valueSpan);
        }
        if (outIndex == -1)
        {
            *ret = -1;
        }
        else
        {
            *ret = outIndex + start;
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "StartsWith")]
    public static unsafe void StartsWith(byte* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        bool result = false;
        if (ignoreCase == 1)
        {
            ushort* ptr1 = stackalloc ushort[len];
            var ptr1Span = new Span<ushort>(ptr1, len);
            strSpan.CopyTo(ptr1Span);
            ushort* ptr2 = stackalloc ushort[valueLen];
            var ptr2Span = new Span<ushort>(ptr2, valueLen);
            valueSpan.CopyTo(ptr2Span);
            ToLower(ptr1Span);
            ToLower(ptr2Span);
            result = ptr1Span.StartsWith(ptr2Span);
        }
        else
        {
            result = strSpan.StartsWith(valueSpan);
        }
        if (result)
        {
            *ret = 1;
        }
        else
        {
            *ret = 0;
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "EndsWith")]
    public static unsafe void EndsWith(byte* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        bool result = false;
        if (ignoreCase == 1)
        {
            ushort* ptr1 = stackalloc ushort[len];
            var ptr1Span = new Span<ushort>(ptr1, len);
            strSpan.CopyTo(ptr1Span);
            ushort* ptr2 = stackalloc ushort[valueLen];
            var ptr2Span = new Span<ushort>(ptr2, valueLen);
            valueSpan.CopyTo(ptr2Span);
            ToLower(ptr1Span);
            ToLower(ptr2Span);
            result = ptr1Span.EndsWith(ptr2Span);
        }
        else
        {
            result = strSpan.EndsWith(valueSpan);
        }
        if (result)
        {
            *ret = 1;
        }
        else
        {
            *ret = 0;
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "Compare")]
    public static unsafe void Compare(int* ret, ushort* strA, int lenA, ushort* strB, int lenB)
    {
        var strASpan = new Span<ushort>(strA, lenA);
        var strBSpan = new Span<ushort>(strB, lenB);
        *ret = strASpan.SequenceCompareTo(strBSpan);
    }

    [UnmanagedCallersOnly(EntryPoint = "Reverse")]
    public static unsafe void Reverse(ushort* ret, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var result = new Span<ushort>(ret, len);
        strSpan.CopyTo(result);
        result.Reverse();
    }

    [UnmanagedCallersOnly(EntryPoint = "Trim")]
    public static unsafe void Trim(ushort* ret, int* outLen, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.Trim(whiteSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "TrimStr")]
    public static unsafe void TrimStr(ushort* ret, int* outLen, ushort* str, int len, ushort* value, int valueLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.Trim(valueSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "TrimStart")]
    public static unsafe void TrimStart(ushort* ret, int* outLen, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimStart(whiteSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "TrimStartStr")]
    public static unsafe void TrimStartStr(ushort* ret, int* outLen, ushort* str, int len, ushort* value, int valueLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimStart(valueSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "TrimEnd")]
    public static unsafe void TrimEnd(ushort* ret, int* outLen, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimEnd(whiteSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "TrimEndStr")]
    public static unsafe void TrimEndStr(ushort* ret, int* outLen, ushort* str, int len, ushort* value, int valueLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimEnd(valueSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "ToLower")]
    public static unsafe void ToLower(ushort* ret, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strCpy = new Span<ushort>(ret, len);
        strSpan.CopyTo(strCpy);
        ToLower(strCpy);
    }

    [UnmanagedCallersOnly(EntryPoint = "ToUpper")]
    public static unsafe void ToUpper(ushort* ret, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strCpy = new Span<ushort>(ret, len);
        strSpan.CopyTo(strCpy);
        ToUpper(strCpy);
    }

    [UnmanagedCallersOnly(EntryPoint = "Substring")]
    public static unsafe void Substring(ushort* ret, ushort* str, int len, int start, int count)
    {
        var strSpan = new Span<ushort>(str, len);
        var strCpy = new Span<ushort>(ret, count);
        strSpan.Slice(start, count).CopyTo(strCpy);
    }

    [UnmanagedCallersOnly(EntryPoint = "Concat")]
    public static unsafe void Concat(ushort* ret, ushort* strA, int lenA, ushort* strB, int lenB)
    {
        var strASpan = new Span<ushort>(strA, lenA);
        var strBSpan = new Span<ushort>(strB, lenB);
        var strCpy = new Span<ushort>(ret, lenA + lenB);
        strASpan.CopyTo(strCpy);
        strBSpan.CopyTo(strCpy.Slice(lenA));
    }

    [UnmanagedCallersOnly(EntryPoint = "Equals")]
    public static unsafe void Equals(byte *ret, ushort* strA, int lenA, ushort* strB, int lenB)
    {
        var strASpan = new Span<ushort>(strA, lenA);
        var strBSpan = new Span<ushort>(strB, lenB);
        if (strASpan.SequenceEqual(strBSpan))
        {
            *ret = 1;
        }
        else
        {
            *ret = 0;
        }
    }
}
