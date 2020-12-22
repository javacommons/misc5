#include <iostream>
#include <iomanip>
#include "strconv.h"

int main()
{
    using namespace std;
    ansi_ostream osw(std::cout);
    cout << 1 << U8(" texto漢字 ") << std::string(U8(" otro texto漢字 ")) << 1.2345 << std::endl;
    osw << 1 << U8(" texto漢字 ") << std::string(U8(" otro texto漢字 ")) << 1.2345 << std::endl;
    osw << 1 << WIDE(" texto漢字 ") << std::wstring(WIDE(" otro texto漢字 ")) << 1.2345 << std::endl;
#ifdef __cpp_char8_t
    //cout << 1 << u8" texto漢字 " << std::u8string(u8" otro texto漢字 ") << 1.2345 << std::endl;
    osw << 1 << u8" char8_t漢字 " << std::u8string(u8" u8string漢字 ") << 1.2345 << std::endl;
#endif
    int x = 123;
    osw << setw(5) << setiosflags(ios::left) << x << "abc" << endl;
    double A = 100;
    double B = 2001.5251;
    double C = 201455.2646;

    // We can use setbase(16) here instead of hex

    // formatting
    osw << hex << left << showbase << nouppercase;

    // actual printed part
    osw << (long long)A << endl;

    // We can use dec here instead of setbase(10)

    // formatting
    osw << setbase(10) << right << setw(15)
        << setfill('_') << showpos
        << fixed << setprecision(2);

    // actual printed part
    osw << B << endl;

    // formatting
    osw << scientific << uppercase
        << noshowpos << setprecision(9);

    // actual printed part
    osw << C << endl;
    return 0;
}
