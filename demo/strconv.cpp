#include "strconv.h"
#include <iostream>
#include <string>

int main(void)
{
    std::string nameUtf8 = u8"太郎";
    int age = 15;
    std::cout << utf8_to_ansi(format(u8"ハロー、私の名前は %s。 年は %d だ!", nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA(u8"ハロー、私の名前は %s。 年は %d だ!", nameUtf8.c_str(), age) << std::endl;
    std::wstring nameWide = L"花子";
    age = 23;
    std::cout << wide_to_ansi(format(L"ハロー、私の名前は %s。 年は %d だ!", nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(L"ハロー、私の名前は %s。 年は %d だ!", nameWide.c_str(), age) << std::endl;
    return 0;
}
