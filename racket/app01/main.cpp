#include "apiv1.hpp"
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



json api_open_archive_for_read(const json &args)
{
    auto copy = args;
    copy["api"] = "api_open_archive_for_read";
    cout << utf8_to_ansi(copy.dump(4)) << endl;
    auto path = args["path"].get<std::string>();
    auto archive_path = utf8_to_wide(path);
    cout << utf8_to_ansi(path) << endl;
    int r;
    struct archive *a = archive_read_new();
    archive_read_support_filter_all(a); // https://manpages.debian.org/stretch/libarchive-dev/libarchive_changes.3.en.html
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename_w(a, archive_path.c_str(), 10240))) {
        std::cout << "Could not open:" << wide_to_utf8(archive_path) << std::endl;
        return false;
    }
    auto addr = address_to_string(a);
    //return json({{"archive", addr}, {"path", path}});
    return json({{"archive", addr}});
}

json api_archive_read_next_header(const json &args)
{
    auto copy = args;
    copy["api"] = "api_archive_read_next_header";
    //cout << utf8_to_ansi(copy.dump(4)) << endl;
    auto addr = args["archive"].get<std::string>();
    struct archive *a = (struct archive *)string_to_address(addr);
    struct archive_entry *entry;
    int r;
    r = archive_read_next_header(a, &entry);
    if (r == ARCHIVE_EOF)
        return false;
    if (r < ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN)
        return false;
    auto entry_addr = address_to_string(entry);
    std::wstring entry_pathname = archive_entry_pathname_w(entry);
    la_int64_t entry_size = archive_entry_size(entry);
    time_t mtime = archive_entry_mtime(entry);
    copy["entry"] = entry_addr;
    copy["pathname"] = wide_to_utf8(entry_pathname);;
    copy["size"] = entry_size;
    copy["mtime"] = mtime;
    return copy;
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
    json archive = api_open_archive_for_read(json{{"path", msys2TarXz}});
    cout << archive.dump() << endl;
    for(;;) {
        json entry = api_archive_read_next_header(archive);
        cout << entry.dump() << endl;
        if(false==entry) {
            break;
        }
    }

    return 0;
}
