#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include "strconv2.hpp"

#include "qtcommon.hpp"

class My : public QApplication {
    Q_OBJECT
public:
    My(int &argc, char **argv) : QApplication(argc, argv) {
    }
    bool download(QUrl &url, QFile &file) {
        MyDownloader dl;
        return dl.download(url, file);
    }
public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
        //qInfo() << bytesReceived << "/" << bytesTotal;
        my_io.printf("\r%lld/%lld", bytesReceived, bytesTotal);
    }
};

int main(int argc, char *argv[])
{
   myInstallMessageHandler();
   My a(argc, argv);

   qDebug() << QDir::currentPath();

   qDebug() << a.arguments().size();
   qDebug() << a.arguments();

   qDebug() << a.applicationFilePath();

   qDebug() << a.applicationDirPath();

   QString cmd = QString("%1/dark.exe").arg(a.applicationDirPath());

   qDebug() << cmd;

   //_wsystem(cmd.toStdWString().c_str());

   //system("pause");

   //exit(0);

   if(a.arguments().size() < 3) {
       system("pause");
       QProcess self;
       QDir out3("@out3");
       return self.execute(a.applicationFilePath(), QStringList() << "vs2019" << out3.absolutePath());
   }

   /*
#if 0x1
    QTemporaryFile file(QDir::tempPath()+"/XXXXXX.zip");
#else
    QTemporaryFile file;
#endif
    qDebug() << "file.fileName():" << file.fileName();
    file.open();
    qDebug() << "file.fileName():" << file.fileName();
    file.close();
    qDebug() << "file.fileName():" << file.fileName();
    QFile file2(file.fileName());
    qDebug() << file2.exists();
    */

#if 0x0
    QTemporaryDir dir;
#else
    QTemporaryDir dir("XXXXXX.tmp");
    //dir.setAutoRemove(false);
    dir.setAutoRemove(true);
#endif
    qDebug() << "dir.path():" << dir.path();
    QDir dir2(dir.path());
    qDebug() << dir2.exists();
    QUrl dl_url("https://aka.ms/vs/16/release/VC_redist.x86.exe");
    //QString fpath = dir.filePath("VC_redist.x86.exe");
    QString dl_path = dir.filePath(dl_url.fileName());
    qDebug() << dl_path;
    QFile dl_file(dl_path);
    MyDownloader dl;
    a.download(dl_url, dl_file);
    QProcess proc;
    QDir out("@out");
    out.removeRecursively();
    proc.execute(cmd, QStringList() << "-nologo" << "-x" << "@out" << dl_path);
    QStringList filter;
    filter << "*.cab";
    QDirIterator it(out.path(),
                    filter,
                    QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    files.sort();
    qDebug() << files;
    //QString cab = files[0];
    //QDir out2("@out2");
    QDir out2(a.arguments()[2]);
    out2.removeRecursively();
    foreach(QString cab, files) {
        qDebug() << cab;
        QFileInfo cabInfo(cab);
        QFileInfo cabDirInfo(cabInfo.dir().path());
        QString subFolder = cabDirInfo.fileName();
        qDebug() << "subFolder=" << subFolder;
        QProcess proc2;
        QDir out2sub(out2.absolutePath()+"/"+subFolder);
        out2.mkpath(out2sub.absolutePath());
        QStringList args2;
        args2 << cab << "-F:*.*" << out2sub.absolutePath();
        qDebug() << args2;
        proc2.execute("expand.exe", args2);
    }
    qInfo() << "finished!";
    return 0;
}

/*
Microsoft Visual C++ 2015-2019 Redistributable
https://aka.ms/vs/16/release/VC_redist.x86.exe
https://aka.ms/vs/16/release/VC_redist.x64.exe
 */

#include "main.moc"

#if 0x0
    QString fpath = dir.filePath("msys2-i686-latest.tar.xz");
    qDebug() << fpath;
    QUrl dl_url("http://repo.msys2.org/distrib/msys2-i686-latest.tar.xz");
    QFile dl_file(dir.filePath("msys2-i686-latest.tar.xz"));
#endif
