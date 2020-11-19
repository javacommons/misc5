#ifndef QTCOMMON_HPP
#define QTCOMMON_HPP

#include <QtCore>
#include <QtNetwork>
#include "strconv2.hpp"

static strconv::io my_io;

static inline void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    Q_UNUSED(context);
    switch (type) {
    case QtDebugMsg:
        my_io.printf("[Debug] %s\n", msg.toUtf8().constData());
        break;
    case QtInfoMsg:
        my_io.printf("[Info] %s\n", msg.toUtf8().constData());
        break;
    case QtWarningMsg:
        my_io.printf("[Warning] %s\n", msg.toUtf8().constData());
        break;
    case QtCriticalMsg:
        my_io.printf("[Critical] %s\n", msg.toUtf8().constData());
        break;
    case QtFatalMsg:
        my_io.printf("[Fatal] %s\n", msg.toUtf8().constData());
        abort();
    }
}

static inline void myInstallMessageHandler() {
    qInstallMessageHandler(myMessageOutput);
}

class MyDownloader : public QObject {
    Q_OBJECT
public:
    MyDownloader() : QObject() {
    }
    bool download(QUrl &url, QFile &file) {
        my_io.printfW(L"Download: %s\n", url.toString().toStdWString().c_str());
        QNetworkRequest req(url);
        QNetworkAccessManager nam;
        QNetworkReply *rep = nam.get(req);
        connect(rep, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(downloadProgress(qint64, qint64)));
        QEventLoop loop;
        while(!rep->isFinished()) {
            loop.processEvents(QEventLoop::ExcludeUserInputEvents);
        }
#if 0x0
        QList<QByteArray> headerNames = rep->rawHeaderList();
        foreach(QByteArray headerName, headerNames) {
            qDebug() << headerName << rep->rawHeader(headerName);
        }
#endif
        if(rep->hasRawHeader("Location")) {
            QByteArray loc = rep->rawHeader("Location");
            QUrl newUrl(loc);
            return download(newUrl, file);
        }
        file.open(QIODevice::WriteOnly);
        file.write(rep->readAll());
        file.close();
        my_io.printf("\n");
        my_io.printfW(L"Downloaded: %s\n", file.fileName().toStdWString().c_str());
        return true;
    }
public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
        if(bytesTotal == 0) return;
        my_io.printf("\r%lld/%lld", bytesReceived, bytesTotal);
    }
};

#endif // QTCOMMON_HPP
