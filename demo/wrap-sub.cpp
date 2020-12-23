#include "strconv.h"
#include <iostream>
#include <iomanip>

namespace std
{
    static inline std::string format(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        std::string s = vformat(format, args);
        va_end(args);
        return s;
    }
} // namespace std

void sub()
{
    using namespace std;
    //unicode_ostream aout(cout);
    unicode_ostream aout(cout, GetConsoleCP());

#ifdef __cpp_char8_t
    aout << 1 << u8" char8_t*漢字© " << std::u8string(u8" u8string漢字© ") << 1.2345 << std::endl;
#endif

    //aout << 1 << u8" char*漢字 " << std::string(u8" string漢字 ") << 1.2345 << std::endl;
    aout << 1 << U8(" char*漢字© ") << std::string(U8(" string漢字© ")) << 1.2345 << std::endl;
    aout << 1 << L" wchar_t*漢字© " << std::wstring(L" wstring漢字© ") << 1.2345 << std::endl;
    aout << ::format(U8("format漢字")) << endl;
    aout << std::format(U8("format漢字")) << endl;

    double A = 100;
    double B = 2001.5251;

    // 書式指定(A) hex の代わりに setbase(16) を使うこともできます
    aout << hex << left << showbase << nouppercase;
    // 実際の印字処理(A)
    aout << (long long)A << endl;

    // 書式指定(B) setbase(10) の代わりに dec を使うこともできます
    aout << setbase(10) << right << setw(15)
         << setfill('_') << showpos
         << fixed << setprecision(2);
    // 実際の印字処理(B)
    aout << B << endl;
}

void sub2(unicode_ostream &aout)
{
    using namespace std;

#ifdef __cpp_char8_t
    aout << 1 << u8" char8_t*漢字© " << std::u8string(u8" u8string漢字© ") << 1.2345 << std::endl;
#endif

    //aout << 1 << u8" char*漢字 " << std::string(u8" string漢字 ") << 1.2345 << std::endl;
    aout << 1 << U8(" char*漢字© ") << std::string(U8(" string漢字© ")) << 1.2345 << std::endl;
    aout << 1 << L" wchar_t*漢字© " << std::wstring(L" wstring漢字© ") << 1.2345 << std::endl;

    double A = 100;
    double B = 2001.5251;

    // 書式指定(A) hex の代わりに setbase(16) を使うこともできます
    aout << hex << left << showbase << nouppercase;
    // 実際の印字処理(A)
    aout << (long long)A << endl;

    // 書式指定(B) setbase(10) の代わりに dec を使うこともできます
    aout << setbase(10) << right << setw(15)
         << setfill('_') << showpos
         << fixed << setprecision(2);
    // 実際の印字処理(B)
    aout << B << endl;
}

void sub3(/*const*/ std::ostream &aout)
{
    using namespace std;

    double A = 100;
    double B = 2001.5251;

    // 書式指定(A) hex の代わりに setbase(16) を使うこともできます
    aout << hex << left << showbase << nouppercase;
    // 実際の印字処理(A)
    aout << (long long)A << endl;

    // 書式指定(B) setbase(10) の代わりに dec を使うこともできます
    aout << setbase(10) << right << setw(15)
         << setfill('_') << showpos
         << fixed << setprecision(2);
    // 実際の印字処理(B)
    aout << B << endl;
}
