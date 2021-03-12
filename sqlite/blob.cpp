
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

struct User
{
    int id;
    std::string name;
    std::vector<char> hash; //  binary format
    std::unique_ptr<std::string> timestamp;
};

inline auto initStorage(const std::string &path) {
    using namespace sqlite_orm;
    auto storage = make_storage("blob.sqlite",
                                make_table("users",
                                           make_column("id", &User::id, primary_key()),
                                           make_column("name", &User::name),
                                           make_column("hash", &User::hash),
                                           make_column("timestamp", &User::timestamp, default_value(datetime("now", "local")))));
    storage.pragma.auto_vacuum(true);
    storage.sync_schema();
    return storage;
}

using Storage = decltype(initStorage(""));

static std::unique_ptr<Storage> storage;

std::string now()
{
    return storage->select(sqlite_orm::datetime("now", "localtime")).front();
}

int main(int, char **)
{
    using namespace sqlite_orm;
#if 0x0
    auto storage = make_storage("blob.sqlite",
                                make_table("users",
                                           make_column("id", &User::id, primary_key()),
                                           make_column("name", &User::name),
                                           make_column("hash", &User::hash),
                                           make_column("timestamp", &User::timestamp, default_value(datetime("now", "local")))));
    storage.pragma.auto_vacuum(true);
    storage.sync_schema();
#endif
    storage = std::make_unique<Storage>(initStorage("blob.sqlite"));
    storage->remove_all<User>();

    User alex = {
        .id = 0,
        .name = "Alex",
        .hash = {0x10, 0x20, 0x30, 0x40},
        .timestamp = std::make_unique<std::string>(now())};
    alex.id = storage->insert(alex);
    User tom = {
        .id = 0,
        .name = "Tom",
        .hash = {0x11, 0x22, 0x33, 0x44},
        //.timestamp = storage.select(sqlite_orm::datetime("now", "localtime")).front()
    };
    tom.id = storage->insert(tom);

    cout << "users count = " << storage->count<User>() << endl;

    cout << "alex = " << storage->dump(storage->get<User>(alex.id)) << endl;

    auto hash = storage->get<User>(alex.id).hash;
    assert(hash.size() == 4);
    assert(hash[0] == 0x10);
    assert(hash[1] == 0x20);
    assert(hash[2] == 0x30);
    assert(hash[3] == 0x40);

    for (auto &user : storage->iterate<User>())
    {
        cout << storage->dump(user) << endl;
    }

    storage->backup_to("bk.sqlite");

    return 0;
}
