#include "strconv.h"

static inline bool check_cp(const std::string &s, UINT codepage)
{
    std::wstring wide = cp_to_wide(s, codepage);
    return s == wide_to_cp(wide, codepage);
}

static inline bool check_cp_ansi(const std::string &s)
{
    return check_cp(s, CP_ACP);
}

static inline bool check_cp_utf8(const std::string &s)
{
    return check_cp(s, CP_UTF8);
}

static inline bool check_cp_sjis(const std::string &s)
{
    return check_cp(s, 932);
}

static inline void conout(std::ostream &ostrm, const wchar_t *format, ...)
{
  va_list args;
  va_start(args, format);
  std::wstring s = vformat(format, args);
  va_end(args);
  ostrm << wide_to_cp(s, GetConsoleCP()) << std::flush;
}
static inline void conout(std::ostream &ostrm, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  std::string s = vformat(format, args);
  va_end(args);
  ostrm << utf8_to_cp(s, GetConsoleCP()) << std::flush;
}

class strconv_console
{
};

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
        WriteConsoleW(std_err,
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
    std::wstring s = vformat(format, args);
    va_end(args);
    DWORD n;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                  s.c_str(),
                  s.size(),
                  &n,
                  NULL);
}
