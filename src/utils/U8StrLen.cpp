#include "utils.hpp"
#include <codecvt>
#include <cwchar>
#include <locale>

using namespace std;

size_t	U8StrLen(const u8string & str)
{
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convert;
    u16string wstr16 = convert.from_bytes(reinterpret_cast<const char*>(str.c_str()));

    size_t  width = 0;

    for (char16_t wc : wstr16) {
        int w = wcwidth(wc);
        if (w > 0) width += w;
    }

    return width;
}
