#define STRCONV_FMTLIB
#define FMT_HEADER_ONLY
#include "strconv.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age) << std::endl;
    std::wstring nameWide = L"花子";
    age = 23;
    std::cout << wide_to_ansi(format(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age) << std::endl;

    cout << outputA(WIDE("[outputA] ハロー、私の名前は {}。 年は {} だ!"), nameWide, age) << endl;
    cout << outputA(U8("[outputA] ハロー、私の名前は {}。 年は {} だ!"), nameUtf8, age) << endl;

    return 0;
}
