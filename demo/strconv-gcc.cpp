#include "strconv.h"
#include <iostream>
#include <string>

void msgbox(const std::wstring &caption, UINT uType = MB_OK, const wchar_t *format = NULL, ...)
{
    std::wstring s;
    if (!format)
    {
        s = caption;
    }
    else
    {
        va_list args;
        va_start(args, format);
        s = vformat(format, args);
        va_end(args);
    }
    MessageBoxW(NULL, s.c_str(), caption.c_str(), uType);
}

int main(void)
{
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format("ハロー、私の名前は %s。 年は %d だ!", nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA("ハロー、私の名前は %s。 年は %d だ!", nameUtf8.c_str(), age) << std::endl;
    msgbox(L"msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©msgboxテスト©");
    msgbox(L"msgboxテスト", MB_OK, L"test=%d", 123);
    std::wstring nameWide = L"花子";
    age = 23;
    std::cout << wide_to_ansi(format(L"ハロー、私の名前は %s。 年は %d だ!", nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(L"ハロー、私の名前は %s。 年は %d だ!", nameWide.c_str(), age) << std::endl;
    return 0;
}
