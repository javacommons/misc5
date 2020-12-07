#include "libarchive.h"

#include <iostream>
#include <filesystem>
#include <map>
#include <regex>

#include <archive.h>
#include <archive_entry.h>
#include <sys/utime.h>
#include "strconv.h"
#include "strutil.h"
#include "vardecl.h"
#include "apiv1.hpp"

using namespace std;

LibArchive::LibArchive()
{
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

void *get_handle_addr(const json &j, const std::string &name)
{
    auto addr = j[name].get<std::string>();
    return string_to_address(addr);
}
void set_handle_addr(json &j, const std::string &name, void *p)
{
    auto addr = address_to_string(p);
    j[name] = addr;
}

std::string to_native_path(const std::string &s)
{
    std::filesystem::path path = utf8_to_wide(s);
    auto native = path.native();
    replace_all(native, L"\\", L"/");
    native = std::regex_replace(native, std::wregex(L"/+$"), L"");
    return wide_to_utf8(native);
}

json api_open_archive(const json &args)
{
    auto copy = args;
    copy["api"] = "api_open_archive_for_extract";
    //cout << utf8_to_ansi(copy.dump(4)) << endl;
    auto path = to_native_path(args["path"].get<std::string>());
    auto target = to_native_path(args["target"].get<std::string>());
    auto archive_path = utf8_to_wide(path);
    //cout << utf8_to_ansi(path) << endl;
    int r;
    struct archive *a = archive_read_new();
    archive_read_support_filter_all(a); // https://manpages.debian.org/stretch/libarchive-dev/libarchive_changes.3.en.html
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename_w(a, archive_path.c_str(), 10240))) {
        //std::cout << "Could not open:" << wide_to_utf8(archive_path) << std::endl;
        return false;
    }
    auto params = get_hendle_params(a);
    set_handle_addr(params, "archive", a);
    params["path"] = path;
    params["target"] = target;
    set_hendle_params(a, params);
    auto result = json({});
    set_handle_addr(result, "archive", a);
    return result;
}

json api_close_archive(const json &args)
{
    auto copy = args;
    copy["api"] = "api_close_archive";
    //cout << utf8_to_ansi(copy.dump(4)) << endl;
    struct archive *a = (struct archive *)get_handle_addr(args, "archive");
    archive_read_close(a);
    archive_read_free(a);
    return true;
}

json api_archive_get_params(const json &args)
{
    auto copy = args;
    copy["api"] = "api_archive_get_params";
    //cout << utf8_to_ansi(copy.dump(4)) << endl;
    struct archive *a = (struct archive *)get_handle_addr(args, "archive");
    return get_hendle_params(a);
}

json api_archive_next_entry(const json &args)
{
    auto copy = args;
    copy["api"] = "api_archive_read_next_header";
    struct archive *a = (struct archive *)get_handle_addr(args, "archive");
    struct archive_entry *entry;
    int r;
    r = archive_read_next_header(a, &entry);
    if (r == ARCHIVE_EOF)
        return false;
    if (r < ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN)
        return false;
    //auto entry_addr = address_to_string(entry);
    std::wstring entry_pathname = archive_entry_pathname_w(entry);
    la_int64_t entry_size = archive_entry_size(entry);
    time_t mtime = archive_entry_mtime(entry);
    //copy["entry"] = entry_addr;
    set_handle_addr(copy, "entry", entry);
    copy["pathname"] = wide_to_utf8(entry_pathname);;
    copy["size"] = entry_size;
    copy["mtime"] = mtime;
    copy["isDir"] = ends_with(entry_pathname, L"/");
    return copy;
}

json api_archive_entry_write(const json &args)
{
    auto copy = args;
    copy["api"] = "api_archive_extract_entry";
    auto pathname = args["pathname"].get<std::string>();
    //if(pathname == "") return false;
    auto params = api_archive_get_params(args);
    auto target = params["target"].get<std::string>();
    //cout << target << " + " << pathname << endl;
    std::string writePath = to_native_path(target + "/" + pathname);
    copy["writePath"] = writePath;
    //cout << realpath << endl;
    bool isDir = args["isDir"];
    struct archive *a = (struct archive *)get_handle_addr(args, "archive");
    struct archive_entry *entry = (struct archive_entry *)get_handle_addr(args, "entry");

    time_t mtime = archive_entry_mtime(entry);
    std::wstring expFilePath = utf8_to_wide(writePath);
    if(isDir) {
        std::filesystem::create_directories(expFilePath);
        return copy;
    }
    std::filesystem::path file = expFilePath;
    std::filesystem::path dir = file.parent_path();
    std::filesystem::create_directories(dir);
    if(std::filesystem::exists(file)) return copy;
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
    return copy;
}
