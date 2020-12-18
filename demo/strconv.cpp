//#include "strconvFmt.h"
#include "strconv.h"
#include <iostream>
#include <string>
#include <fstream>

//using namespace std;

bool utf8_check_is_valid(const std::string &string) // http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
{
    int c, i, ix, n, j;
    for (i = 0, ix = string.length(); i < ix; i++)
    {
        c = (unsigned char)string[i];
        //if (c==0x09 || c==0x0a || c==0x0d || (0x20 <= c && c <= 0x7e) ) n = 0; // is_printable_ascii
        if (0x00 <= c && c <= 0x7f)
            n = 0; // 0bbbbbbb
        else if ((c & 0xE0) == 0xC0)
            n = 1; // 110bbbbb
        else if (c == 0xed && i < (ix - 1) && ((unsigned char)string[i + 1] & 0xa0) == 0xa0)
            return false; //U+d800 to U+dfff
        else if ((c & 0xF0) == 0xE0)
            n = 2; // 1110bbbb
        else if ((c & 0xF8) == 0xF0)
            n = 3; // 11110bbb
        //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else
            return false;
        for (j = 0; j < n && i < ix; j++)
        { // n bytes matching 10bbbbbb follow ?
            if ((++i == ix) || (((unsigned char)string[i] & 0xC0) != 0x80))
                return false;
        }
    }
    return true;
}

bool getlineJ(std::istream &istrm, std::wstring &line)
{
    std::string s;
    if (!std::getline(istrm, s))
    {
        line = L"";
        return false;
    }
    if (utf8_check_is_valid(s))
        line = utf8_to_wide(s);
    else
        line = sjis_to_wide(s);
    return true;
}

bool getlineJ(std::istream &istrm, std::string &line)
{
    std::string s;
    if (!std::getline(istrm, s))
    {
        line = "";
        return false;
    }
    if (utf8_check_is_valid(s))
        line = s;
    else
        line = sjis_to_utf8(s);
    return true;
}

int main(void)
{
//wcout.imbue(std::locale("Japanese"));
//wcout.imbue(std::locale(""));
//setlocale(LC_ALL, "Japanese");
#if 0x0
    std::string nameUtf8 = U8("太郎");
    int age = 15;
    std::cout << utf8_to_ansi(format(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age)) << std::endl;
    std::cout << formatA(U8("ハロー、私の名前は %s。 年は %d だ!"), nameUtf8.c_str(), age) << std::endl;
    formatA(cout, U8("ハロー、私の名前は %s。 年は %d だ!\n"), nameUtf8.c_str(), age);
#endif
    std::string s;
    std::cout << getlineJ(std::cin, s) << std::endl;
    std::cout << s.size() << std::endl;
    formatA(std::cout, U8("s=%s\n"), s.c_str());
    std::wstring nameWide = L"花子";
    int
        age = 23;
    std::cout << wide_to_ansi(format(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age)) << std::endl;
    std::cout << formatA(WIDE("ハロー、私の名前は %s。 年は %d だ!"), nameWide.c_str(), age) << std::endl;
    format(std::cout, WIDE("[wcout] ハロー、私の名前は %s。 年は %d だ!\n"), nameWide.c_str(), age);

#if 0x0
    std::vector<int> v = {1, 2, 3};
    cout << outputA(WIDE("[outputA] ハロー、私の名前は {}。 年は {} だ!"), nameWide, age) << endl;
    cout << outputA(U8("[outputA] ハロー、私の名前は {}。 年は {} だ!"), nameUtf8, v) << endl;
    cout << output(U8("[output] ハロー、私の名前は {}。 年は {} だ!"), nameUtf8, v) << endl;
    outputA(cout, WIDE("[outputA] ハロー、私の名前は {}。 年は {} だ!\n"), nameWide, age);
    outputA(cout, U8("[outputA] ハロー、私の名前は {}。 年は {} だ!\n"), nameUtf8, v);

    ofstream outputfile("test.txt");
    output(outputfile, U8("[output] ハロー、私の名前は {}。 年は {} だ!\n"), nameUtf8, v);
    outputA(outputfile, U8("[outputA] ハロー、私の名前は {}。 年は {} だ!\n"), nameUtf8, v);
    format(outputfile, U8("[format] ハロー、私の名前は %s。 年は %d だ!\n"), nameUtf8.c_str(), age);
    format(outputfile, WIDE("[format] ハロー、私の名前は %s。 年は %d だ!\n"), nameWide.c_str(), age);
    outputfile.close();
#endif

    return 0;
}
