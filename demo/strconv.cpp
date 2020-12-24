#include "strconv.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class CMyClass
{
    friend std::ostream &operator<<(std::ostream &stream, const CMyClass &value);
};

// 扱う値は第二引数に指定します。また、連続してストリーム出力できるように、戻り値では第一引数で受け取ったストリームを返します。

std::ostream &
operator<<(std::ostream &stream, const CMyClass &value)
{
    stream << u8"テスト";
    return stream;
};

int main()
{
#ifdef ANSI_ONLY
    unicode_ostream aout(cout);
#else
    unicode_ostream aout(cout, GetConsoleCP()); // chcp 65001 とすると, © が c に化けずに表示される
#endif
    CMyClass mc;
    aout << mc << endl;
    double pi = 4 * atan(1.0);
    aout << "π(1)=" << pi << endl;
    aout << "π(2)=" << format("%.2f", pi) << endl;

    aout << 1 << u8" char*漢字© " << std::string(u8" string漢字© ") << 1.2345 << std::endl;
    aout << 2 << L" wchar_t*漢字© " << std::wstring(L" wstring漢字© ") << 1.2345 << std::endl;

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

    return 0;
}
