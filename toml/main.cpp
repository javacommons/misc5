#include <toml.hpp>
#include <fstream> //required for toml::parse_file()
#include <iostream>

void do_something_with_string_values(toml::node &node)
{

}

int main()
{
    auto config = toml::parse_file("configuration.toml");

    // get key-value pairs
    std::string_view library_name = config["library"]["name"].value_or("");
    std::string_view library_author = config["library"]["authors"][0].value_or("");
    int64_t depends_on_cpp_version = config["dependencies"]["cpp"].value_or(0);

    // modify the data
    config.insert_or_assign("alternatives", toml::array{
                                                "cpptoml",
                                                "toml11",
                                                "Boost.TOML"});

    // iterate & visit over the data
    for (auto &&[k, v] : config)
    {
        v.visit([](auto &node) noexcept {
            std::cout << node << "\n";
            if constexpr (toml::is_string<decltype(node)>)
                do_something_with_string_values(node);
        });
    }

    // re-serialize as TOML
    std::cout << config << "\n";

    // re-serialize as JSON
    std::cout << toml::json_formatter{config} << "\n";
    return 0;
}
