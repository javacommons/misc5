#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <iomanip>

#include "nameof.hpp"

int main()
{
    std::ifstream i("../json/nlohmann.json");
    json j;
    i >> j;

    //std::ofstream o("pretty.json");
    //o << std::setw(4) << j << std::endl;
    std::cout << std::setw(8) << j << std::endl;
    json j2;
    j2.push_back("foo");
    j2.push_back(1);
    j2.push_back(true);
    // also use emplace_back
    j2.emplace_back(1.78);
    std::cout << std::setw(2) << j2 << std::endl;
    json j3;
    j3["none"].push_back(123.4);
    std::cout << std::setw(2) << j3 << ' ' << nameof::nameof_enum(j3.type()) << j3.type_name() << std::endl;
}
