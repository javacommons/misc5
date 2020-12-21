#ifndef LIBARCHIVE_H
#define LIBARCHIVE_H

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#if 0x0
class LibArchive
{
public:
    LibArchive();
};
#endif

json api_open_archive(const json &args);
json api_close_archive(const json &args);
json api_archive_get_params(const json &args);
json api_archive_next_entry(const json &args);
json api_archive_entry_write(const json &args);

#endif // LIBARCHIVE_H
