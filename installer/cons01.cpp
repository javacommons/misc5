#include <QtCore>
#include <QtNetwork>
#include <string>
#include "strconvQt.h"

#include "dll01.h"

int run_cmd(const std::string &cmd)
{
    QString cmdline = utf8_to_qstr(cmd);
    qDebug() << cmdline;
    QProcess process;
    process.setProcessChannelMode(QProcess::ForwardedChannels);
    process.start(cmdline);
    process.waitForFinished(-1);
    return process.exitCode();
}

int run_busybox(const std::string &cmd)
{
    QString cmdline = utf8_to_qstr(cmd);
    qDebug() << cmdline;
    QString app_dir = qApp->applicationDirPath();
    cmdline = QString("\"%1\\busybox32.exe\" time %2").arg(app_dir).arg(cmdline);
    qDebug() << cmdline;
    return run_cmd(qstr_to_utf8(cmdline));
}

int run_curl(const std::string &cmd)
{
    QString cmdline = utf8_to_qstr(cmd);
    qDebug() << QString("curl32 %1").arg(cmdline);
    QString app_dir = qApp->applicationDirPath();
    cmdline = QString("\"%1\\busybox32.exe\" time \"%1\\curl32.exe\" %2").arg(app_dir).arg(cmdline);
    qDebug() << cmdline;
    return run_cmd(qstr_to_utf8(cmdline));
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    int dummy = 0;
    QCoreApplication a(dummy, nullptr);

    qDebug() << "hello";

    //QString app_dir = a.applicationDirPath();
    QString app_dir = qApp->applicationDirPath();

#if 0x0
    std::string ad = get_app_dir();
    unicode_ostream uout(std::cout);
    uout << ad << std::endl;
#endif

    qDebug() << qApp->arguments();

    QNetworkAccessManager nam;
    QUrl url = QUrl("https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz");
    QNetworkRequest req(url);
    QNetworkReply *reply = nam.head(req);
    QEventLoop loop;
    while(!reply->isFinished())
    {
        loop.processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    qDebug() << reply->rawHeaderList();
    qDebug() << reply->rawHeader("Etag");

#if 0x1
    qDebug() << run_busybox("ls -l");
    //qDebug() << run_busybox("curl32 --etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz");
    qDebug() << run_curl("-D headers.txt --etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz");
    qDebug() << run_busybox("rm -rf my-msys2.tmp");
    qDebug() << run_busybox("mkdir -p my-msys2.tmp");
    qDebug() << run_busybox("tar -xf msys2-x86_64-latest.tar.xz -C my-msys2.tmp --strip-components 1");
#endif
    return 0;
}
