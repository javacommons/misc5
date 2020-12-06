#ifndef LIBARCHIVE_H
#define LIBARCHIVE_H

#include <archive.h>
#include <archive_entry.h>
#include <string>

class LibArchive
{
public:
    LibArchive();
};

bool extract_archive(const std::wstring &archive_path, const std::wstring &output_path);

#endif // LIBARCHIVE_H
