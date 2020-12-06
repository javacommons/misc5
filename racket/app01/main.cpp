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

typedef json (*json_api)(const json &args);
std::map<std::string, json_api> json_api_map;
void register_json_api(const std::string &name, json_api func)
{
    json_api_map[name] = func;
}
json_api retrieve_json_api(const std::string &name)
{
    if(json_api_map.count(name)==0) return nullptr;
    return json_api_map[name];
}

#define REGISTER_JSON_API(X) (register_json_api(#X, X))
#define RETRIEVE_JSON_API(X) (retrieve_json_api(#X))

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

#if 0x0
    json api_open_archive(const json &args);
    json api_close_archive(const json &args);
    json api_archive_get_params(const json &args);
    json api_archive_next_entry(const json &args);
    json api_archive_entry_extract(const json &args);
#endif
    REGISTER_JSON_API(api_open_archive);
    REGISTER_JSON_API(api_close_archive);
    REGISTER_JSON_API(api_archive_get_params);
    REGISTER_JSON_API(api_archive_next_entry);
    REGISTER_JSON_API(api_archive_entry_extract);

    std::string msys2TarXz = u8R"(C:\Users\Public\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)";
    //json archive = api_open_archive(json{{"path", msys2TarXz}, {"target", "D:/temp/"}});
    json archive = RETRIEVE_JSON_API(api_open_archive)(json{{"path", msys2TarXz}, {"target", "D:/temp/"}});
    if(archive==false) return 1;
    for(;;) {
        //json entry = api_archive_next_entry(archive);
        json entry = RETRIEVE_JSON_API(api_archive_next_entry)(archive);
        if(false==entry) {
            break;
        }
        auto pathname = entry["pathname"].get<std::string>();
        auto realname = std::regex_replace(pathname, std::regex("^[^/]+/(.*)$"), "$1");
        entry["pathname"] = realname;
        //auto written = api_archive_entry_extract(entry);
        auto written = RETRIEVE_JSON_API(api_archive_entry_extract)(entry);
        if(written==false) break;
        bool isDir = entry["isDir"];
        std::string indicator = isDir?"[D] ":"[F] ";
        cout << indicator << written["extractPath"] << endl;
    }
    //json params = api_archive_get_params(archive);
    json params = RETRIEVE_JSON_API(api_archive_get_params)(archive);
    //cout << params << endl;
    RETRIEVE_JSON_API(api_close_archive)(archive);

    return 0;
}
