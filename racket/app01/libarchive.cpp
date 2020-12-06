#include "libarchive.h"

#include <iostream>
#include <filesystem>
#include <map>
#include <regex>

#include <archive.h>
#include <archive_entry.h>
#include <sys/utime.h>
#include "strconv.h"
#include "vardecl.h"
#include "apiv1.hpp"

using namespace std;

LibArchive::LibArchive()
{
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
inline bool ends_with(std::wstring const & value, std::wstring const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::string replaceAll(std::string &replacedStr, std::string from, std::string to) // https://www.sejuku.net/blog/54493
{
    unsigned int pos = replacedStr.find(from);
    int toLen = to.length();
    if (from.empty()) {
        return replacedStr;
    }
    while ((pos = replacedStr.find(from, pos)) != std::string::npos) {
        replacedStr.replace(pos, from.length(), to);
        pos += toLen;
    }
    return replacedStr;
}
std::wstring replaceAll(std::wstring &replacedStr, std::wstring from, std::wstring to) // https://www.sejuku.net/blog/54493
{
    unsigned int pos = replacedStr.find(from);
    int toLen = to.length();
    if (from.empty()) {
        return replacedStr;
    }
    while ((pos = replacedStr.find(from, pos)) != std::string::npos) {
        replacedStr.replace(pos, from.length(), to);
        pos += toLen;
    }
    return replacedStr;
}

static std::map<void *, json> handle_map;
json get_hendle_params(void *p)
{
    if(handle_map.count(p) > 0) return handle_map[p];
    return json::object();
}
void set_hendle_params(void *p, const json &j)
{
    handle_map[p] = j;
}

std::string to_native_path(const std::string &s)
{
    std::filesystem::path path = utf8_to_wide(s);
    auto native = path.native();
    //replaceAll(native, L"/", L"\\");
    replaceAll(native, L"\\", L"/");
    wcout << native << endl;
    //native = std::regex_replace(native, std::wregex(L"\\\\+$"), L"");
    native = std::regex_replace(native, std::wregex(L"/+$"), L"");
    return wide_to_utf8(native);
}

json api_open_archive_for_extract(const json &args)
{
    auto copy = args;
    copy["api"] = "api_open_archive_for_read";
    cout << utf8_to_ansi(copy.dump(4)) << endl;
    auto path = to_native_path(args["path"].get<std::string>());
    auto target = to_native_path(args["target"].get<std::string>());
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
    auto params = get_hendle_params(a);
    params["archive"] = addr;
    params["path"] = path;
    params["target"] = target;
    set_hendle_params(a, params);
    cout << "handle_map[a].dump()=" << get_hendle_params(a) << endl;
    return json({{"archive", addr}});
}

json api_close_archive(const json &args)
{
    auto copy = args;
    copy["api"] = "api_close_archive";
    cout << utf8_to_ansi(copy.dump(4)) << endl;
    auto addr = args["archive"].get<std::string>();
    struct archive *a = (struct archive *)string_to_address(addr);
    archive_read_close(a);
    archive_read_free(a);
    return true;
}

json api_archive_get_params(const json &args)
{
    auto copy = args;
    copy["api"] = "api_archive_get_params";
    cout << utf8_to_ansi(copy.dump(4)) << endl;
    auto addr = args["archive"].get<std::string>();
    struct archive *a = (struct archive *)string_to_address(addr);
    return get_hendle_params(a);
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
    copy["isDir"] = ends_with(entry_pathname, L"/");
    return copy;
}

json api_archive_extract_entry(const json &args)
{
    auto pathname = args["pathname"].get<std::string>();
    if(pathname == "") return false;
    auto params = api_archive_get_params(args);
    auto target = params["target"].get<std::string>();
    cout << target << " + " << pathname << endl;
    return true;
}


bool extract_archive(const std::wstring &archive_path, const std::wstring &output_path) {
    //QDir dir(output_path);
    //dir.removeRecursively();
    int r;
    struct archive *a = archive_read_new();
#if 0x0
    archive_read_support_compression_all(a);
#else
    archive_read_support_filter_all(a); // https://manpages.debian.org/stretch/libarchive-dev/libarchive_changes.3.en.html
#endif
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename_w(a, archive_path.c_str(), 10240))) {
        std::cout << "Could not open:" << wide_to_utf8(archive_path) << std::endl;
        return false;
    }
    std::cout << "Open:" << wide_to_utf8(archive_path) << std::endl;
    for (;;) {
        struct archive_entry *entry;
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        if (r < ARCHIVE_WARN)
            return false;
        std::wstring entry_pathname = archive_entry_pathname_w(entry);
        //qDebug() << "entry_pathname:" << entry_pathname;
        la_int64_t entry_size = archive_entry_size(entry);
        UNUSED_VARIABLE(entry_size);
        //qDebug() << "entry_size:" << entry_size;
        time_t mtime = archive_entry_mtime(entry);
        //QDateTime mtime_dt = QDateTime::fromTime_t(mtime);
        //qDebug() << "mtime:" << mtime_dt;
        std::wstring expFilePath = output_path + L"/" + entry_pathname;
        //qDebug() << "expFilePath:" << expFilePath;
        if(ends_with(entry_pathname, L"/")) {
            std::filesystem::create_directories(expFilePath);
            //QDir dir;
            //dir.mkpath(expFilePath);
            continue;
        }
        //QFile file(expFilePath);
        std::filesystem::path file = expFilePath;
        //QFileInfo finfo(file);
        //QDir dir = finfo.dir();
        std::filesystem::path dir = file.parent_path();
        //qDebug() << dir.absolutePath();
        //dir.mkpath(dir.absolutePath());
        std::filesystem::create_directories(dir);
        FILE *fp;;
        if((fp = _wfopen(expFilePath.c_str(), L"wb"))) {
            int fd = fileno(fp);
            archive_read_data_into_fd(a, fd);
            fclose(fp);
            _utimbuf utbuff;
            utbuff.actime = mtime;
            utbuff.modtime = mtime;
            _wutime(expFilePath.c_str(), &utbuff);
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    return true;
}
