#include "../common/strconv2.hpp"
#include <iostream>
#include <fstream> //  ifstream, ofstream
#include <stdio.h>

using namespace std;
using namespace strconv2;
//using strconv2::utf8_to_sjis;

int main()
{
    string_io io;
    io._dump();
    cout << "Hello World!(3)" << endl;
    std::string utf8 = "abc漢字©";
    cout << utf8 << endl;
    cout << utf8_to_sjis(utf8) << endl;
    wstring wide = L"abc漢字©";
    io.printfW(L"%s\n", wide.c_str());
    wstring w2 = io.promptW(L"wide入力: ");
    io.writelnW(w2);
    string sjis = io.promptJ("sjis input: ");
    io.writelnJ(sjis);

    cout << io.setenv(u8"AAA", u8"xyz変数©") << endl;
    io.write("AAA=");
    io.writeln(io.getenv("AAA"));
    io.writeln(io.getenv("PATH"));

    ifstream fin;
    fin.open("input1.txt");
    io.set_in_stream(fin);
    std::string line;
    while (io.getline(line)) {
        io.writelnJ("success");
        io.writeln(line);
    }
    fin.close();

    return 0;
}
