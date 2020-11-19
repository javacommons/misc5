#include "../common/strconv2.hpp"
#include <iostream>
#include <fstream> //  ifstream, ofstream
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace strconv2;
//using strconv2::utf8_to_sjis;

std::wstring ProcessIdToNameW(DWORD processId)
{
    std::wstring ret;
    HANDLE handle = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId
    );
    if (handle)
    {
        std::vector<wchar_t> buffer(10240);
        DWORD buffer_size = buffer.size();
        if (QueryFullProcessImageNameW(handle, 0, &buffer[0], &buffer_size))
        {
            ret = &buffer[0];
            ret = ret.substr(ret.find_last_of('\\') + 1);
        }
        else
        {
            ret = L"";
        }
        CloseHandle(handle);
    }
    else
    {
        ret = L"";
    }
    return ret;
}

std::wstring GetConsoleProgramW() {
    HWND hwnd = GetConsoleWindow();
    if (!hwnd) return L"";
    DWORD proc_id;
    DWORD th_id = GetWindowThreadProcessId(hwnd, &proc_id);
    return ProcessIdToNameW(proc_id);
}

int main()
{
    string_io io;
    io._dump();

    io.printfW(L"GetConsoleProgramW()=%s\n", GetConsoleProgramW().c_str());

    cout << "Hello World!(3)" << endl;
    wstring wide = L"abc漢字©";
    io.printfW(L"wide.c_str()=%s\n", wide.c_str());
    wstring w2 = io.promptW(L"wide入力: ");
    io.printfW(L"w2=%s\n", w2.c_str());
    string sjis = io.promptJ("sjis入力: ");
    io.printfJ("sjis=%s\n", sjis.c_str());

    cout << io.setenv(u8"AAA", u8"=xyz変数©") << endl;
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
