#include <QtCore>
#include "lib01.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << Lib01::add2(11, 22);

    return 0;
}
