#include "sqlite01_widget.h"
#include "sqlite01_common.h"

#include <sqlite_orm/sqlite_orm.h>

#include <yaml-cpp/yaml.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdint.h>
#include <boost/stacktrace.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::flush;

static std::string db_now();

struct User
{
    int64_t id;
    std::string name;
    std::string timestamp = db_now();
};

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
struct convert<User> {
    static Node encode(const User& rhs) {
        Node node;
        node["id"] = rhs.id;
        node["name"] = rhs.name;
        node["timestamp"] = rhs.timestamp;
        return node;
    }
    static bool decode(const Node& node, User& rhs) {
        if(!node.IsMap()) return false;
        rhs.id = node["id"].as<int64_t>();
        rhs.name = node["name"].as<std::string>();
        rhs.timestamp = node["timestamp"].as<std::string>();
        return true;
    }
};
}

inline auto init_db(const std::string &path)
{
    using namespace sqlite_orm;
    auto db = make_storage(path,
                           make_table("users",
                                      make_column("id", &User::id, primary_key()),
                                      make_column("name", &User::name, unique()),
                                      make_column("timestamp", &User::timestamp)));
    db.sync_schema();
    db.pragma.auto_vacuum(true);
    return db;
}

using DB = decltype(init_db(""));

static std::unique_ptr<DB> db;

std::string db_now()
{
    //return db->select(sqlite_orm::datetime("now", "localtime")).front();
    return db->select(sqlite_orm::strftime("%Y-%m-%d %H:%M:%f", "now")).front();
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    Sqlite01_Widget w;
    w.show();
    qDebug() << "hello漢字";

    using namespace sqlite_orm;

    db = std::make_unique<DB>(init_db("blob.sqlite"));

    db->remove_all<User>();

    User alex = {
        .id = 0,
        .name = "Alex",
        //.timestamp = db_now()
    };
    alex.id = db->insert(alex);

    User tom = {
        .id = 0,
        .name = "Tom",
        //.timestamp = db_now()
    };
    tom.id = db->insert(tom);

    cout << "users count = " << db->count<User>() << endl;
    cout << "alex = " << db->dump(db->get<User>(alex.id)) << endl;
    cout << "tom  = " << db->dump(db->get<User>(tom.id)) << endl;

    YAML::Node yaml;
    for (auto &user : db->iterate<User>())
    {
        cout << db->dump(user) << endl;
        //yaml.push_back(user);
        yaml["users"].push_back(user);
    }
    std::ofstream fout("users.yaml");
    fout << yaml << endl;
    fout.close();

    db->backup_to("bk.sqlite");

    try
    {
        alex.id = db->insert(alex); // UNIQUE constraint failed: users.name: constraint failed
    }
    catch (std::exception &e)
    {
        cerr << "std::exception: " << e.what() << std::endl;
        cerr << " at " << __FILE__ << ':' << __LINE__ << endl;
        cerr << boost::stacktrace::stacktrace() << flush;
    }
    catch (...)
    {
        cerr << "unknown exeption" << endl;
        cerr << " at " << __FILE__ << ':' << __LINE__ << endl;
        cerr << boost::stacktrace::stacktrace() << flush;
    }

    return a.exec();
}
