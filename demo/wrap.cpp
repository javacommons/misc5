#include <iostream>
#include <iomanip>
#include "strconv.h"

class ansi_ostream
{
private:
    std::ostream &m_ostrm;

public:
    ansi_ostream(std::ostream &ostrm) : m_ostrm(ostrm) {}
    template <typename T>
    ansi_ostream &operator<<(const T &x)
    {
        m_ostrm << x;
        return *this;
    }
    ansi_ostream &operator<<(const std::string &x)
    {
        m_ostrm << "<string>" << utf8_to_ansi(x) << "</string>";
        return *this;
    }
    ansi_ostream &operator<<(const char *x)
    {
        m_ostrm << "<char*>" << utf8_to_ansi(x) << "</char*>";
        return *this;
    }
    ansi_ostream &operator<<(const std::wstring &x)
    {
        m_ostrm << "<wstring>" << wide_to_ansi(x) << "</wstring>";
        return *this;
    }
    ansi_ostream &operator<<(const wchar_t *x)
    {
        m_ostrm << "<wchar_t*>" << wide_to_ansi(x) << "</wchar_t*>";
        return *this;
    }
#ifdef __cpp_char8_t
    ansi_ostream &operator<<(const std::u8string &x)
    {
        m_ostrm << "<u8string>" << utf8_to_ansi((const char *)x.c_str()) << "</u8tring>";
        return *this;
    }
    ansi_ostream &operator<<(const char8_t *x)
    {
        m_ostrm << "<char8_t*>" << utf8_to_ansi((const char *)x) << "</char8_t*>";
        return *this;
    }
#endif    
    ansi_ostream &operator<<(std::ostream &(*pf)(std::ostream &)) // For manipulators...
    {
        m_ostrm << pf;
        return *this;
    }
    ansi_ostream &operator<<(std::basic_ios<char> &(*pf)(std::basic_ios<char> &)) // For manipulators...
    {
        m_ostrm << pf;
        return *this;
    }
};

int main()
{
    using namespace std;
    ansi_ostream osw(std::cout);
    osw << 1 << U8(" texto漢字 ") << std::string(U8(" otro texto漢字 ")) << 1.2345 << std::endl;
    osw << 1 << WIDE(" texto漢字 ") << std::wstring(WIDE(" otro texto漢字 ")) << 1.2345 << std::endl;
#ifdef __cpp_char8_t
    osw << 1 << u8" texto漢字 " << std::u8string(u8" otro texto漢字 ") << 1.2345 << std::endl;
#endif
    int x = 123;
    osw << setw(5) << setiosflags(ios::left) << x << "abc" << endl;
    double A = 100;
    double B = 2001.5251;
    double C = 201455.2646;

    // We can use setbase(16) here instead of hex

    // formatting
    osw << hex << left << showbase << nouppercase;

    // actual printed part
    osw << (long long)A << endl;

    // We can use dec here instead of setbase(10)

    // formatting
    osw << setbase(10) << right << setw(15)
        << setfill('_') << showpos
        << fixed << setprecision(2);

    // actual printed part
    osw << B << endl;

    // formatting
    osw << scientific << uppercase
        << noshowpos << setprecision(9);

    // actual printed part
    osw << C << endl;
    return 0;
}
