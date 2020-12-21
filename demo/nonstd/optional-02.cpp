#include "nonstd/optional.hpp"

#include <iostream>
#include <vector>
#include "strconv.h"

using nonstd::optional;

struct V
{
    int v;

    V( int v )
    : v( v ) {}
};

int main()
{
    try
    {
        int x = 42;
//      V s;        // V has no default constructor
        V t(x);     // Ok

        std::vector< optional<V> > v(3);
        v[0] = t;

        std::cout << "v[0].value().v: " << v[0].value().v << "\n";
        if(v[1])
        {
            format(std::cout, "then\n");

        }
        else
        {
            format(std::cout, "else\n");
        }
        std::cout << "v[1].value().v: " << v[1].value().v << "\n";
    }
    catch( std::exception const & e )
    {
        std::cout << "Error: " << e.what() << "\n";
    }
}
