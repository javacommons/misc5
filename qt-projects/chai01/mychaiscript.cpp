#include "mychaiscript.hpp"

#include <chaiscript/chaiscript.hpp>
#ifdef STATIC_LINK_CHAI_STDLIB
#include <chaiscript/chaiscript_stdlib.hpp>
#endif

std::string helloWorld(const std::string &t_name) {
    return "Hello " + t_name + "!";
}

#ifdef STATIC_LINK_CHAI_STDLIB
MyChaiscript::MyChaiscript() : chaiscript::ChaiScript(chaiscript::Std_Lib::library())
#else
MyChaiscript::MyChaiscript()
#endif
{
    this->add(chaiscript::fun(&helloWorld), "helloWorld");
}
