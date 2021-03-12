
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

static std::string now();

struct User
{
    int id;
    std::string name;
    std::vector<char> hash; // binary format
    std::string timestamp = now();
};

inline auto initDB(const std::string &path) {
    using namespace sqlite_orm;
    auto db = make_storage("blob.sqlite",
                                make_table("users",
                                           make_column("id", &User::id, primary_key()),
                                           make_column("name", &User::name),
                                           make_column("hash", &User::hash),
                                           make_column("timestamp", &User::timestamp, default_value(datetime("now", "local")))));
    db.pragma.auto_vacuum(true);
    db.sync_schema();
    return db;
}

using DB = decltype(initDB(""));

static std::unique_ptr<DB> db;

std::string now()
{
    //return db->select(sqlite_orm::datetime("now", "localtime")).front();
    return db->select(sqlite_orm::strftime("%Y-%m-%d %H:%M:%f", "now")).front();
}

int main(int, char **)
{
    using namespace sqlite_orm;
    db = std::make_unique<DB>(initDB("blob.sqlite"));
    db->remove_all<User>();

    User alex = {
        .id = 0,
        .name = "Alex",
        .hash = {0x10, 0x20, 0x30, 0x40},
        //.timestamp = now()
        };
    alex.id = db->insert(alex);

    User tom = {
        .id = 0,
        .name = "Tom",
        .hash = {0x11, 0x22, 0x33, 0x44},
        //.timestamp = now()
    };
    tom.id = db->insert(tom);

    cout << "users count = " << db->count<User>() << endl;

    cout << "alex = " << db->dump(db->get<User>(alex.id)) << endl;
    cout << "tom  = " << db->dump(db->get<User>(tom.id)) << endl;

    auto hash = db->get<User>(alex.id).hash;
    assert(hash.size() == 4);
    assert(hash[0] == 0x10);
    assert(hash[1] == 0x20);
    assert(hash[2] == 0x30);
    assert(hash[3] == 0x40);

    for (auto &user : db->iterate<User>())
    {
        cout << db->dump(user) << endl;
    }

    db->backup_to("bk.sqlite");

    return 0;
}
