#include "strconv.h"
#include <iostream>
#include <string>

#define U8(X) ((const char *)u8##X)
#define U8X(X) ((const char *)u8## #X)

#define WIDE(X) L##X
#define WIDEX(X) L## #X

int main(void)
{
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age) << std::endl;
    std::wstring nameWide = L"花子";
    age = 23;
    std::cout << wide_to_ansi(format(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(WIDEX("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age) << std::endl;
    return 0;
}
