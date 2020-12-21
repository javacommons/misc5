#include "nonstd/variant.hpp"

#include <iostream>
#include <string>

typedef nonstd::variant< char, int, long, std::string > myvar;

inline std::ostream & operator<<( std::ostream & os, const myvar & v )
{
    os << "[variant:";
    switch( v.index() )
    {
        case 0: os << nonstd::get<0>( v ); break;
        case 1: os << nonstd::get<1>( v ); break;
        case 2: os << nonstd::get<2>( v ); break;
        case 3: os << nonstd::get<3>( v ); break;
        default: os << "unexpected index";
    }
    return os << "]";
}

int main()
{
    myvar var;

    var = 'v'; std::cout << "char:" << var << "\n";
    var =  7 ; std::cout << "int:"  << var << "\n";
    var = 42L; std::cout << "long:" << var << "\n";
    var = std::string("hello, world"); std::cout << "std::string:" << var << "\n";
    var = "hello, world2"; std::cout << "std::string:" << var << "\n";
}
