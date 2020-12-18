#include "strconvFmt.h"
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    //wcout.imbue(std::locale("Japanese"));
    //wcout.imbue(std::locale(""));
    //setlocale(LC_ALL, "Japanese");
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age) << std::endl;
    formatA(cout, U8("ハロー、私の名前は %s。 年は %d だ!\n"), nameUtf8.c_str(), age);
    std::wstring nameWide = L"花子";
    age = 23;
    std::cout << wide_to_ansi(format(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age) << std::endl;
    format(cout, WIDE("[wcout] ハロー、私の名前は %s。 年は %d だ!\n"), nameWide.c_str(), age);

    std::vector<int> v = {1, 2, 3};
    cout << outputA(WIDE("[outputA] ハロー、私の名前は {}。 年は {} だ!"), nameWide, age) << endl;
    cout << outputA(U8("[outputA] ハロー、私の名前は {}。 年は {} だ!"), nameUtf8, v) << endl;
    cout << output(U8("[output] ハロー、私の名前は {}。 年は {} だ!"), nameUtf8, v) << endl;
    outputA(cout, WIDE("[outputA] ハロー、私の名前は {}。 年は {} だ!\n"), nameWide, age);
    outputA(cout, U8("[outputA] ハロー、私の名前は {}。 年は {} だ!\n"), nameUtf8, v);

    return 0;
}
