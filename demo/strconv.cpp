//#include "strconvFmt.h"
#include "strconv.h"
#include <iostream>
#include <string>
#include <fstream>

int main(void)
{
#if 0x1
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age) << std::endl;
    formatA(std::cout, U8("ハロー、私の名前は %s。 年は %d だ!\n"), nameUtf8.c_str(), age);
#endif
    std::wstring nameWide = L"花子";
    //int
    age = 23;
    std::cout << wide_to_ansi(format(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age) << std::endl;
    formatA(std::cout, WIDE("ハロー、私の名前は %s。 年は %d だ!\n"), nameWide.c_str(), age);

    return 0;
}
