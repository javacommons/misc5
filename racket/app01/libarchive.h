#ifndef LIBARCHIVE_H
#define LIBARCHIVE_H

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class LibArchive
{
public:
    LibArchive();
};

//bool extract_archive(const std::wstring &archive_path, const std::wstring &output_path);
json api_open_archive_for_extract(const json &args);
json api_close_archive(const json &args);
json api_archive_get_params(const json &args);
json api_archive_read_next_header(const json &args);

#endif // LIBARCHIVE_H
