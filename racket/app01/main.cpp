#include "libarchive.h"
#include "apiv1.hpp"
#include <QtCore>
#include <iostream>
#include <filesystem>
#include <map>
#include <regex>
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
    json archive = api_open_archive_for_extract(json{{"path", msys2TarXz}, {"target", "D:/temp/"}});
    cout << archive << endl;
    //exit(0);
    for(;;) {
        json entry = api_archive_read_next_header(archive);
        //cout << entry.dump() << endl;
        if(false==entry) {
            break;
        }
        //cout << entry["pathname"].dump() << endl;
        auto pathname = entry["pathname"].get<std::string>();
        auto realname = std::regex_replace(pathname, std::regex("^[^/]+/(.*)$"), "$1");
        cout << realname << " isDir=" << entry["isDir"] << endl;
        //if(r=="") break;
    }
    json params = api_archive_get_params(archive);
    cout << params << endl;
    api_close_archive(archive);

    return 0;
}
