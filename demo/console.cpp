#include <windows.h>
#include <string>
#include "strconv.h"

static inline void writeline(const std::wstring &line)
{
    HANDLE std_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD n;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                  line.c_str(),
                  line.size(),
                  &n,
                  NULL);
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                  L"\n",
                  1,
                  &n,
                  NULL);
}

static inline std::wstring readline(const std::wstring &prompt)
{
    if (prompt != L"")
    {
        HANDLE std_err = ::GetStdHandle(STD_ERROR_HANDLE);
        DWORD n;
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                      prompt.c_str(),
                      prompt.size(),
                      &n,
                      NULL);
    }
    HANDLE std_in = ::GetStdHandle(STD_INPUT_HANDLE);
    wchar_t buffer[1];
    DWORD n;
    std::wstring result;
    while (::ReadConsoleW(std_in, buffer, 1, &n, NULL))
    {
        if (buffer[0] == 13)
            continue;
        if (buffer[0] == 10)
            break;
        result += buffer[0];
    }
    return result;
}

static inline void writef(const wchar_t *format, ...)
{
    va_list args;
    va_start(args, format);
    int len = _vsnwprintf(nullptr, 0, format, args);
    std::vector<wchar_t> buffer(len + 1);
    _vsnwprintf(&buffer[0], len + 1, format, args);
    va_end(args);
    std::wstring s = &buffer[0];
    DWORD n;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                  s.c_str(),
                  s.size(),
                  &n,
                  NULL);
}

int main()
{
    std::wstring msg = readline(L"input: ");
    writeline(msg);
    writef(L"msg=[%s]\n", msg.c_str());
    return 0;
}