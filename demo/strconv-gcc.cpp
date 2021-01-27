#include "strconv.h"
#include <iostream>
#include <string>

void msgbox(const wchar_t *caption, UINT uType=MB_OK, const wchar_t *format=NULL,...)
{
    MessageBoxW(NULL, caption, caption, uType);
}

int main(void)
{
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format("ハロー、私の名前は %s。 年は %d だ!", nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA("ハロー、私の名前は %s。 年は %d だ!", nameUtf8.c_str(), age) << std::endl;
    msgbox(L"msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©");
    std::wstring nameWide = L"花子";
    age = 23;
    std::cout << wide_to_ansi(format(L"ハロー、私の名前は %s。 年は %d だ!", nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(L"ハロー、私の名前は %s。 年は %d だ!", nameWide.c_str(), age) << std::endl;
    return 0;
}
