#include <QtCore>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>

#include "strconvQt.h"

namespace YAML {
template<>
struct convert<QString> {
    static Node encode(const QString& rhs) {
        Node node;
        node = qstr_to_utf8(rhs);
        return node;
    }
    static bool decode(const Node& node, QString& rhs) {
        if(!node.IsScalar()) return false;
        std::string s = node.as<std::string>();
        rhs = utf8_to_qstr(s);
        return true;
    }
};
}

namespace YAML {
template<>
struct convert<QDateTime> {
    static Node encode(const QDateTime& rhs) {
        Node node;
        node = qstr_to_utf8(rhs.toString("yyyy-MM-dd HH:mm:ss"));
        return node;
    }
    static bool decode(const Node& node, QDateTime& rhs) {
        if(!node.IsScalar()) return false;
        std::string s = node.as<std::string>();
        rhs = QDateTime::fromString(utf8_to_qstr(s), "yyyy-MM-dd HH:mm:ss");
        return true;
    }
};
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDateTime dt = QDateTime::currentDateTime();
    qDebug() << dt;

    YAML::Node config = YAML::LoadFile("main.yaml");

    if (config["lastLogin"])
    {
        //std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";
    }

    const std::string username = config["username"].as<std::string>();
    const std::string password = config["password"].as<std::string>();

    QDateTime my_dt = config["my-datetime"].as<QDateTime>();
    qDebug() << my_dt;

    std::string my_dt2 = config["my-datetime"].as<std::string>();
    qDebug() << utf8_to_qstr(my_dt2);

    QString my_dt3 = config["my-datetime"].as<QString>();
    qDebug() << my_dt3;

    YAML::Binary binary = config["my-data"].as<YAML::Binary>();
    const unsigned char *data = binary.data();
    std::size_t size = binary.size();

    std::string bin((const char *)data, size);
    std::cout << "bin=" << bin << std::endl;

    //login(username, password);
    //config["lastLogin"] = getCurrentDateTime();
    std::string str = "abc";
    config["bin-data"] = YAML::Binary((const unsigned char *)str.data(), str.size());
    config["dt-data"] = dt;

    std::ofstream fout("config.yaml");
    fout << config;

    YAML::Emitter emitter;
    //emitter << YAML::Binary("Hello, World!", 13);
    emitter << YAML::Binary((const unsigned char *)str.data(), str.size());
    std::cout << emitter.c_str() << std::endl;

    return 0;
}
