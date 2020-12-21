#include <iostream>
#include <iomanip>

class ostreamWrapper
{
private:
    std::ostream &m_ostrm;

public:
    ostreamWrapper(std::ostream &ostrm) : m_ostrm(ostrm) {}

    template <typename T>
    ostreamWrapper &operator<<(const T &x)
    {
        m_ostrm << x;
        return *this;
    }
    ostreamWrapper &operator<<(const std::string &x)
    {
        m_ostrm << "<string>" << x << "</string>";
        return *this;
    }
    ostreamWrapper &operator<<(const char *x)
    {
        m_ostrm << "<char*>" << x << "</char*>";
        return *this;
    }
    ostreamWrapper &operator<<(std::ostream &(*pf)(std::ostream &))
    {
        // For manipulators...
        m_ostrm << pf;
        return *this;
    }
    ostreamWrapper &operator<<(std::basic_ios<char> &(*pf)(std::basic_ios<char> &))
    {
        // For manipulators...
        m_ostrm << pf;
        return *this;
    }
};

int main()
{
    using namespace std;
    ostreamWrapper osw(std::cout);
    osw << 1 << " texto " << std::string(" otro texto ") << 1.2345 << std::endl;
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
