#include <QtCore>
//#include "lib01.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //qDebug() << Lib01::add2(11, 22);
    qDebug() << "hello!";
    QFile File(QCoreApplication::applicationDirPath() + "/config.cfg");
    qDebug() << File.fileName();
    QFile File2(QCoreApplication::applicationFilePath());
    qDebug() << File2.fileName();

    return 0;
}
