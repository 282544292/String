using System.Runtime.InteropServices;
using System.Text;

namespace CSharpStrLib;

public class String
{
    private readonly static ushort[] whiteSpan = { 32, 9, 10, 11, 12, 13 };

    public static void ToLower(Span<ushort> str)
    {

        for (int i = 0; i < str.Length; i++)
        {
            str[i] = (ushort)char.ToLowerInvariant((char)str[i]);
        }
        return;
    }

    public static void ToUpper(Span<ushort> str)
    {
        for (int i = 0; i < str.Length; i++)
        {
            str[i] = (ushort)char.ToUpperInvariant((char)str[i]);
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "MReplace")]
    public static unsafe void MReplace(ushort* ret, int outLen, ushort* str, int len, ushort* oldChar, int oldLen, ushort* newChar, int newLen)
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

    [UnmanagedCallersOnly(EntryPoint = "MContains")]
    public static unsafe void MContains(byte* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
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

    [UnmanagedCallersOnly(EntryPoint = "MIndexOf")]
    public static unsafe void MIndexOf(int* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
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

    [UnmanagedCallersOnly(EntryPoint = "MStartCountIndexOf")]
    public static unsafe void MStartCountIndexOf(int* ret, ushort* str, int len, ushort* value, int valueLen, int start, int count, byte ignoreCase)
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

    [UnmanagedCallersOnly(EntryPoint = "MStartIndexOf")]
    public static unsafe void MStartIndexOf(int* ret, ushort* str, int len, ushort* value, int valueLen, int start, byte ignoreCase)
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

    [UnmanagedCallersOnly(EntryPoint = "MStartsWith")]
    public static unsafe void MStartsWith(byte* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
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

    [UnmanagedCallersOnly(EntryPoint = "MEndsWith")]
    public static unsafe void MEndsWith(byte* ret, ushort* str, int len, ushort* value, int valueLen, byte ignoreCase)
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

    [UnmanagedCallersOnly(EntryPoint = "MCompare")]
    public static unsafe void MCompare(int* ret, ushort* strA, int lenA, ushort* strB, int lenB)
    {
        var strASpan = new Span<ushort>(strA, lenA);
        var strBSpan = new Span<ushort>(strB, lenB);
        *ret = strASpan.SequenceCompareTo(strBSpan);
    }

    [UnmanagedCallersOnly(EntryPoint = "MReverse")]
    public static unsafe void MReverse(ushort* ret, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var result = new Span<ushort>(ret, len);
        strSpan.CopyTo(result);
        result.Reverse();
    }

    [UnmanagedCallersOnly(EntryPoint = "MTrim")]
    public static unsafe void MTrim(ushort* ret, int* outLen, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.Trim(whiteSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "MTrimStr")]
    public static unsafe void MTrimStr(ushort* ret, int* outLen, ushort* str, int len, ushort* value, int valueLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.Trim(valueSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "MTrimStart")]
    public static unsafe void MTrimStart(ushort* ret, int* outLen, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimStart(whiteSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "MTrimStartStr")]
    public static unsafe void MTrimStartStr(ushort* ret, int* outLen, ushort* str, int len, ushort* value, int valueLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimStart(valueSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "MTrimEnd")]
    public static unsafe void MTrimEnd(ushort* ret, int* outLen, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimEnd(whiteSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "MTrimEndStr")]
    public static unsafe void MTrimEndStr(ushort* ret, int* outLen, ushort* str, int len, ushort* value, int valueLen)
    {
        var strSpan = new Span<ushort>(str, len);
        var valueSpan = new Span<ushort>(value, valueLen);
        var strRet = new Span<ushort>(ret, len);
        var retSpan = strSpan.TrimEnd(valueSpan);
        retSpan.CopyTo(strRet);
        *outLen = retSpan.Length;
    }

    [UnmanagedCallersOnly(EntryPoint = "MToLower")]
    public static unsafe void MToLower(ushort* ret, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strCpy = new Span<ushort>(ret, len);
        strSpan.CopyTo(strCpy);
        ToLower(strCpy);
    }

    [UnmanagedCallersOnly(EntryPoint = "MToUpper")]
    public static unsafe void MToUpper(ushort* ret, ushort* str, int len)
    {
        var strSpan = new Span<ushort>(str, len);
        var strCpy = new Span<ushort>(ret, len);
        strSpan.CopyTo(strCpy);
        ToUpper(strCpy);
    }

    [UnmanagedCallersOnly(EntryPoint = "MSubstring")]
    public static unsafe void MSubstring(ushort* ret, ushort* str, int len, int start, int count)
    {
        var strSpan = new Span<ushort>(str, len);
        var strCpy = new Span<ushort>(ret, count);
        strSpan.Slice(start, count).CopyTo(strCpy);
    }

    [UnmanagedCallersOnly(EntryPoint = "MConcat")]
    public static unsafe void MConcat(byte* ret, byte* strA, int lenA, byte* strB, int lenB)
    {
        var strASpan = new Span<byte>(strA, lenA);
        var strBSpan = new Span<byte>(strB, lenB);
        var strCpy = new Span<byte>(ret, lenA + lenB);
        strASpan.CopyTo(strCpy);
        strBSpan.CopyTo(strCpy.Slice(lenA));
    }

    [UnmanagedCallersOnly(EntryPoint = "MEquals")]
    public static unsafe void MEquals(byte *ret, ushort* strA, int lenA, ushort* strB, int lenB)
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

    [UnmanagedCallersOnly(EntryPoint = "MTryEncodingConvert")]
    public static unsafe sbyte MTryEncodingConvert(byte *ret, long *retLen, byte *str, int len, int encoding1, int encoding2)
    {
        Encoding enc1;
        Encoding enc2;
        try
        {
            enc1 = Encoding.GetEncoding(encoding1);
            enc2 = Encoding.GetEncoding(encoding2);
        }
        catch (Exception)
        {
            return -1;
        }
        string srcString = enc1.GetString(new ReadOnlySpan<byte>(str, len));
        byte[] destBytes = enc2.GetBytes(srcString);
        *retLen = destBytes.Length;
        if (destBytes.Length > *retLen)
        {
            return 0;
        }

        fixed (byte* destPtr = destBytes)
        {
            Buffer.MemoryCopy(destPtr, ret, *retLen, destBytes.Length);
        }
        return 1;
    }
}
