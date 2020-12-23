#include "strconv.h"
#include <iostream>
#include <iomanip>

void sub();
void sub2(unicode_ostream &aout);

int main()
{
    using namespace std;
    //unicode_ostream aout(cout);
    unicode_ostream aout(cout, GetConsoleCP());

#ifdef __cpp_char8_t
    aout << 1 << u8" char8_t*漢字© " << std::u8string(u8" u8string漢字© ") << 1.2345 << std::endl;
#endif

    formatA(cout, u8"formatA-u8 漢字©=%s\n", u8"文字列");

    aout << format(u8"format-u8 漢字©=%s\n", u8"文字列");

#ifdef __cpp_char8_t
    std::wstring wide = char8_to_wide(u8"char8_to_wide(漢字©)");
    aout << wide << endl;
    std::u8string char8 = wide_to_char8(wide);
    aout << char8 << endl;

    std::string ansi = char8_to_ansi(char8);
    cout << ansi << endl;
    char8 = ansi_to_char8(ansi);
    aout << char8 << endl;
 
    std::string sjis = char8_to_sjis(char8);
    cout << sjis << endl;
    char8 = sjis_to_char8(sjis);
    aout << char8 << endl;

    std::string utf8 = char8_to_utf8(char8);
    aout << utf8 << endl;
    char8 = utf8_to_char8(utf8);
    aout << char8 << endl;
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

    //sub();
    //sub2(aout);

    return 0;
}
