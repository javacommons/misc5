#include <iostream>
#include <iomanip>
#include "strconv.h"

int main()
{
    using namespace std;
    ansi_ostream aout(cout);
 
    aout << 1 << u8" char*漢字 " << std::string(u8" string漢字 ") << 1.2345 << std::endl;
    aout << 1 << L" wchar_t*漢字 " << std::wstring(L" wstring漢字 ") << 1.2345 << std::endl;

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
