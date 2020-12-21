#include <iostream>

using namespace std;

class ostreamWrapper
{
private:
    ostream &m_ostrm;

public:
    ostreamWrapper(ostream &ostrm) : m_ostrm(ostrm) {}

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
    ostreamWrapper osw(std::cout);
    osw << 1 << " texto " << std::string(" otro texto ") << 1.2345 << std::endl;
    return 0;
}
