#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

int main()
{
    YAML::Node config = YAML::LoadFile("main.yaml");

    if (config["lastLogin"])
    {
        //std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";
    }

    const std::string username = config["username"].as<std::string>();
    const std::string password = config["password"].as<std::string>();

    YAML::Binary binary = config["my-data"].as<YAML::Binary>();
    const unsigned char *data = binary.data();
    std::size_t size = binary.size();

    std::string bin((const char *)data, size);
    std::cout << "bin=" << bin << std::endl;

    //login(username, password);
    //config["lastLogin"] = getCurrentDateTime();
    std::string str = "abc";
    config["bin-data"] = YAML::Binary((const unsigned char *)str.data(), str.size());

    std::ofstream fout("config.yaml");
    fout << config;

    YAML::Emitter emitter;
    //emitter << YAML::Binary("Hello, World!", 13);
    emitter << YAML::Binary((const unsigned char *)str.data(), str.size());
    std::cout << emitter.c_str();

    return 0;
}