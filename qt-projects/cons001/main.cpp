#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <archive.h>
#include <archive_entry.h>
#include <sys/utime.h>

#include "dialog.h"

bool extract_archive(const QString &archive_path, const QString &output_path) {
    QDir dir(output_path);
    dir.removeRecursively();
    int r;
    struct archive *a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename_w(a, archive_path.toStdWString().c_str(), 10240))) {
        qDebug() << "Could not open:" << archive_path;
        return false;
    }
    for (;;) {
        struct archive_entry *entry;
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        if (r < ARCHIVE_WARN)
            return false;
        QString entry_pathname = QString::fromWCharArray(archive_entry_pathname_w(entry));
        qDebug() << "entry_pathname:" << entry_pathname;
        la_int64_t entry_size = archive_entry_size(entry);
        qDebug() << "entry_size:" << entry_size;
        time_t mtime = archive_entry_mtime(entry);
        QDateTime mtime_dt = QDateTime::fromTime_t(mtime);
        qDebug() << "mtime:" << mtime_dt;
        QString expFilePath = output_path + QString("/") + entry_pathname;
        qDebug() << "expFilePath:" << expFilePath;
        if(entry_pathname.endsWith("/")) {
            QDir dir;
            dir.mkpath(expFilePath);
            continue;
        }
        QFile file(expFilePath);
        QFileInfo finfo(file);
        QDir dir = finfo.dir();
        //qDebug() << dir.absolutePath();
        dir.mkpath(dir.absolutePath());
        if(file.open(QIODevice::WriteOnly)) {
            int fd = file.handle();
            archive_read_data_into_fd(a, fd);
            file.close();
            _utimbuf utbuff;
            utbuff.actime = mtime;
            utbuff.modtime = mtime;
            _wutime(file.fileName().toStdWString().c_str(), &utbuff);
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    return true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "hello!";
    app.setOrganizationName("javacommons");
    app.setApplicationName("cons001");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    Dialog d(nullptr);
    int i = d.exec();                  // 表示、結果を取得
    if( i == QDialog::Accepted ) {
        qDebug() << "QDialog::Accepted";
    } else if( i == QDialog::Rejected ) {
        qDebug() << "QDialog::Rejected";
    }
#if 0x0
    bool b = extract_archive(R"(C:\Users\Public\home\data\msys2-i686-20180320.7z)",
                             R"(C:\Users\Public\home\data\@out)");
    qDebug() << "b:" << b;
#endif
    return 0;
}
