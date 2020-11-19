#include <archive.h>
#include <archive_entry.h>
#include <sys/utime.h>

#include <string>
#include "strconv.h"

#include <filesystem>

#include <iostream>

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

bool extract_archive(const std::wstring &archive_path, const std::wstring &output_path) {
    //QDir dir(output_path);
    //dir.removeRecursively();
    int r;
    struct archive *a = archive_read_new();
    archive_read_support_compression_all(a);
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
        if(fp = _wfopen(expFilePath.c_str(), L"wb")) {
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

int main(int argc, char *argv[])
{
    std::cout << "main(1)" << std::endl;
#if 0x1
    bool b = extract_archive(LR"(C:\root\Dropbox\_data_\msys2-base-x86_64-20200903.tar.xz)",
                             LR"(C:\Users\javac\Documents\misc4\racket\@out.tmp)");
    //qDebug() << "b:" << b;
    std::cout << "main(2)" << b << std::endl;
#endif
    return 0;
}
