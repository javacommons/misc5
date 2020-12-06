#include <QtCore>
#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include "strconv.h"
#include "vardecl.h"

#include <archive.h>
#include <archive_entry.h>
#include <sys/utime.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

namespace data
{
    struct person
    {
        std::string name;
        std::string address;
        int age;
    };
} // namespace ns

namespace data
{
    void to_json(json &j, const person &p)
    {
        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
    }
    void from_json(const json &j, person &p)
    {
        j.at("name").get_to(p.name); // get_to(T& arg) は arg = get<T>() と同じ
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }
} // namespace ns



json open_archive_for_read(const json &args)
{
    cout << utf8_to_ansi(args.dump(4)) << endl;
    nlohmann::json result = false;
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "hello!";
    QFile File(QCoreApplication::applicationDirPath() + "/config.cfg");
    qDebug() << File.fileName();
    QFile File2(QCoreApplication::applicationFilePath());
    qDebug() << File2.fileName();

    namespace fs = std::filesystem;
    // 現在の作業ディレクトリを取得
    fs::path p = fs::current_path();
    std::cout << p << std::endl;

    const std::wstring s = p.wstring();
    qDebug() << wide_to_qstr(s);

    // 現在の作業ディレクトリを設定
    fs::current_path(L"/");
    std::cout << fs::current_path() << std::endl;

    std::map<std::string, double> map = {{"a", 123.0}, {"b", 567.8}};
    nlohmann::json j =  map;
    std::cout << j.dump(4) << std::endl;
    QString tarXzPath = wide_to_qstr(LR"(C:\Users\Public\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)");
    QFile tarXz(tarXzPath);
    qDebug() << tarXz.size();
    std::cout << "main(1)" << std::endl;
#if 0x0
    bool b = extract_archive(LR"(C:\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)",
                             LR"(C:\Users\javac\Documents\misc4\racket\@out.tmp)");
    //qDebug() << "b:" << b;
    std::cout << "main(2)" << b << std::endl;
#endif

    std::string msys2TarXz = u8R"(C:\Users\Public\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)";
    data::person psn;
    psn.name = "tom";
    psn.age = 35;
    psn.address = "new york";
    json r = open_archive_for_read(psn);
    cout << r.dump() << endl;
    //data::variant_map vmap = {{"a", 123}, {"b", "XYZ"}};
    json jj = {{"a", 123}, {"b", "XYZ"}, {"c", {1, 2, 3}}};
    json r2 = open_archive_for_read(jj);
    json r3 = open_archive_for_read(json{{"path", msys2TarXz}, {"b1", "XYZ漢字"}});

    return 0;
}
