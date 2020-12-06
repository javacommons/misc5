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

    std::string msys2TarXz = u8R"(C:\Users\Public\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)";
    json archive = api_open_archive_for_extract(json{{"path", msys2TarXz}, {"target", "D:/temp/"}});
    //cout << archive << endl;
    if(archive==false) return 1;
    //exit(0);
    for(;;) {
        json entry = api_archive_read_next_header(archive);
        if(false==entry) {
            break;
        }
        auto pathname = entry["pathname"].get<std::string>();
        auto realname = std::regex_replace(pathname, std::regex("^[^/]+/(.*)$"), "$1");
        //cout << realname << " isDir=" << entry["isDir"] << endl;
        entry["pathname"] = realname;
        auto written = api_archive_extract_entry(entry);
        if(written==false) break;
        bool isDir = entry["isDir"];
        std::string indicator = isDir?"[D] ":"[F] ";
        cout << indicator << written["extractPath"] << endl;
    }
    json params = api_archive_get_params(archive);
    //cout << params << endl;
    api_close_archive(archive);

    return 0;
}
